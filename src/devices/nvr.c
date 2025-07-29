#include <stdio.h>
#include <stdlib.h>
#include "ibm.h"
#include "device.h"
#include "io.h"
#include "nvr.h"
#include "pic.h"
#include "timer.h"
#include "rtc.h"
#include "paths.h"
#include "config.h"
#include "model.h"
#include "nmi.h"
#include "x86.h"

int oldromset;
int nvrmask = 63;
uint8_t nvrram[128];
int nvraddr;

int nvr_dosave = 0;

typedef struct nvr_t {
        pc_timer_t rtc_timer;
        pc_timer_t onesec_timer;
        pc_timer_t update_end_timer;

        int onesec_cnt;
} nvr_t;

FILE *nvrfopen(char *fn, char *mode) {
        char s[512];
        FILE *f;

        strcpy(s, nvr_path);
        put_backslash(s);
        strcat(s, config_name);
        strcat(s, ".");
        strcat(s, fn);
        pclog("NVR try opening %s\n", s);
        f = fopen(s, mode);
        if (f)
                return f;

        if (mode[0] == 'r') {
                snprintf(s, 512, "%s%s", nvr_default_path, fn);
                return fopen(s, mode);
        } else {
                pclog("Failed to open file '%s' for write\n", s);
                return NULL;
        }
}

void getnvrtime() { time_get(nvrram); }

static void nvr_speed_changed(void *p) {
        nvr_t *nvr = (nvr_t *)p;

        if (!(nvrram[RTC_REGA] & RTC_RS)) {
                timer_disable(&nvr->rtc_timer);
                return;
        } else {
                int c = 1 << ((nvrram[RTC_REGA] & RTC_RS) - 1);
                timer_set_delay_u64(&nvr->rtc_timer, (uint64_t)(RTCCONST * c));
        }
}

static void nvr_rtc(void *p) {
        nvr_t *nvr = (nvr_t *)p;

        if (!(nvrram[RTC_REGA] & RTC_RS)) {
                timer_disable(&nvr->rtc_timer);
                return;
        } else {
                int c = 1 << ((nvrram[RTC_REGA] & RTC_RS) - 1);
                timer_advance_u64(&nvr->rtc_timer, (uint64_t)(RTCCONST * c));
                //                pclog("RTCtime now %f\n",rtctime);
                nvrram[RTC_REGC] |= RTC_PF;
                if (nvrram[RTC_REGB] & RTC_PIE) {
                        nvrram[RTC_REGC] |= RTC_IRQF;
                        if (AMSTRAD)
                                picint(2);
                        else
                                picint(0x100);
                        //                        pclog("RTC int\n");
                }
        }
}

int nvr_update_status = 0;

#define ALARM_DONTCARE 0xc0

int nvr_check_alarm(int nvraddr) {
        return (nvrram[nvraddr + 1] == nvrram[nvraddr] || (nvrram[nvraddr + 1] & ALARM_DONTCARE) == ALARM_DONTCARE);
}

static void nvr_update_end(void *p) {
        //        nvr_t *nvr = (nvr_t *)p;

        if (!(nvrram[RTC_REGB] & RTC_SET)) {
                getnvrtime();
                /* Clear update status. */
                nvr_update_status = 0;

                if (nvr_check_alarm(RTC_SECONDS) && nvr_check_alarm(RTC_MINUTES) && nvr_check_alarm(RTC_HOURS)) {
                        nvrram[RTC_REGC] |= RTC_AF;
                        if (nvrram[RTC_REGB] & RTC_AIE) {
                                nvrram[RTC_REGC] |= RTC_IRQF;
                                if (AMSTRAD)
                                        picint(2);
                                else
                                        picint(0x100);
                        }
                }

                /* The flag and interrupt should be issued on update ended, not started. */
                nvrram[RTC_REGC] |= RTC_UF;
                if (nvrram[RTC_REGB] & RTC_UIE) {
                        nvrram[RTC_REGC] |= RTC_IRQF;
                        if (AMSTRAD)
                                picint(2);
                        else
                                picint(0x100);
                }
        }

        //                pclog("RTC onesec\n");
}

static void nvr_onesec(void *p) {
        nvr_t *nvr = (nvr_t *)p;

        nvr->onesec_cnt++;
        if (nvr->onesec_cnt >= 100) {
                if (!(nvrram[RTC_REGB] & RTC_SET)) {
                        nvr_update_status = RTC_UIP;
                        rtc_tick();

                        timer_set_delay_u64(&nvr->update_end_timer, (uint64_t)((244.0 + 1984.0) * TIMER_USEC));
                }
                nvr->onesec_cnt = 0;
        }
        timer_advance_u64(&nvr->onesec_timer, (uint64_t)(10000 * TIMER_USEC));
}

static void writenvr(uint16_t addr, uint8_t val, void *p) {
        nvr_t *nvr = (nvr_t *)p;
        int c, old;

        cycles -= ISA_CYCLES(8);
        //        printf("Write NVR %03X %02X %02X %04X:%04X %i\n",addr,nvraddr,val,cs>>4,pc,ins);
        if (addr & 1) {
                if (nvraddr == RTC_REGC || nvraddr == RTC_REGD)
                        return; /* Registers C and D are read-only. There's no reason to continue. */
                                //                if (nvraddr == 0x33) pclog("NVRWRITE33 %02X %04X:%04X %i\n",val,CS,pc,ins);
                if (nvraddr > RTC_REGD && nvrram[nvraddr] != val)
                        nvr_dosave = 1;

                old = nvrram[nvraddr];
                nvrram[nvraddr] = val;

                if (nvraddr == RTC_REGA) {
                        //                        pclog("NVR rate %i\n",val&0xF);
                        if (val & RTC_RS) {
                                c = 1 << ((val & RTC_RS) - 1);
                                timer_set_delay_u64(&nvr->rtc_timer, (uint64_t)(RTCCONST * c));
                        } else
                                timer_disable(&nvr->rtc_timer);
                } else {
                        if (nvraddr == RTC_REGB) {
                                if (((old ^ val) & RTC_SET) && (val & RTC_SET)) {
                                        nvrram[RTC_REGA] &= ~RTC_UIP; /* This has to be done according to the datasheet. */
                                        nvrram[RTC_REGB] &= ~RTC_UIE; /* This also has to happen per the specification. */
                                }
                        }

                        if ((nvraddr < RTC_REGA) || (nvraddr == RTC_CENTURY)) {
                                if ((nvraddr != 1) && (nvraddr != 3) && (nvraddr != 5)) {
                                        if ((old != val) && !enable_sync) {
                                                time_update(nvrram, nvraddr);
                                                nvr_dosave = 1;
                                        }
                                }
                        }
                }
        } else {
                nvraddr = val & nvrmask;
                /*PS/2 BIOSes will disable NMIs and expect the watchdog timer to still be able
                  to fire them. I suspect the watchdog is exempt from NMI masking. Currently NMIs
                  are always enabled for PS/2 machines - this would mean that other peripherals
                  could fire NMIs regardless of the mask state, but as there aren't any emulated
                  MCA peripherals that do this it's currently a moot point.*/

                /* Also don't update the NMI mask on Amstrad PCs - actually
                 * ought not to do it for any XT because their NMI mask
                 * register is at 0xA0. But particularly important on the
                 * PC200 and PPC because their video subsystem issues NMIs */
                if (!(models[model]->flags & (MODEL_MCA | MODEL_AMSTRAD))) {
                        nmi_mask = ~val & 0x80;
                }
        }
}

uint8_t readnvr(uint16_t addr, void *p) {
        //        nvr_t *nvr = (nvr_t *)p;
        uint8_t temp;
        //        printf("Read NVR %03X %02X %02X %04X:%04X\n",addr,nvraddr,nvrram[nvraddr],cs>>4,pc);
        cycles -= ISA_CYCLES(8);
        if (addr & 1) {
                if (nvraddr == RTC_REGA)
                        return ((nvrram[RTC_REGA] & 0x7F) | nvr_update_status);
                if (nvraddr == RTC_REGD)
                        nvrram[RTC_REGD] |= RTC_VRT;
                if (nvraddr == RTC_REGC) {
                        if (AMSTRAD)
                                picintc(2);
                        else
                                picintc(0x100);
                        temp = nvrram[RTC_REGC];
                        nvrram[RTC_REGC] = 0;
                        return temp;
                }
                //                if (AMIBIOS && nvraddr==0x36) return 0;
                //                if (nvraddr==0xA) nvrram[0xA]^=0x80;
                return nvrram[nvraddr];
        }
        return nvraddr;
}


static void *nvr_init() {
        nvr_t *nvr = (nvr_t *)malloc(sizeof(nvr_t));
        memset(nvr, 0, sizeof(nvr_t));

        io_sethandler(0x0070, 0x0002, readnvr, NULL, NULL, writenvr, NULL, NULL, nvr);
        timer_add(&nvr->rtc_timer, nvr_rtc, nvr, 1);
        timer_add(&nvr->onesec_timer, nvr_onesec, nvr, 1);
        timer_add(&nvr->update_end_timer, nvr_update_end, nvr, 0);

        return nvr;
}

static void nvr_close(void *p) {
        nvr_t *nvr = (nvr_t *)p;

        free(nvr);
}

device_t nvr_device = {"Motorola MC146818 RTC", 0, nvr_init, nvr_close, NULL, nvr_speed_changed, NULL, NULL, NULL};
