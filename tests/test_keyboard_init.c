#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "ibm.h"
#undef printf
#include "io.h"
#include "keyboard/keyboard_xt.h"

extern uint8_t keyboard_xt_read(uint16_t, void *);
extern void keyboard_xt_write(uint16_t, uint8_t, void *);
extern uint8_t (*port_inb[0x10000][2])(uint16_t, void*);
extern void (*port_outb[0x10000][2])(uint16_t, uint8_t, void*);

void pclog(const char *fmt, ...) {}
void error(const char *fmt, ...) {}
void fatal(const char *fmt, ...) {}
void warning(const char *fmt, ...) {}

uint8_t mem_readb_phys(uint32_t addr) { return 0; }
void mem_writeb_phys(uint32_t addr, uint8_t val) {}
void mem_invalidate_range(uint32_t start, uint32_t end) {}

uint64_t tsc = 0;
int cpu_busspeed = 1;
uint64_t xt_cpu_multi;

#include "private/timer.h"
void timer_add(pc_timer_t *timer, void (*callback)(void *), void *p, int start) { timer->callback = callback; timer->p = p; timer->enabled = start; }
uint32_t timer_target; uint64_t TIMER_USEC; void timer_enable(pc_timer_t *timer) { timer->enabled = 1; } void timer_disable(pc_timer_t *timer) { timer->enabled = 0; }

PPI ppi; int nmi = 0; int nmi_auto_clear = 0; int speakon = 0; int ppispeakon = 0; int speakval = 0; int mem_size = 640; int romset = ROM_AMIXT;
void device_speed_changed() {}
void video_updatetiming() {}
void picint(uint16_t num) {}
void picintc(uint16_t num) {}

int main() {
    io_init();
    keyboard_xt_init();
    for (int p = 0x60; p < 0x64; p++) {
        assert(port_inb[p][0] == keyboard_xt_read);
        assert(port_outb[p][0] == keyboard_xt_write);
    }
    printf("keyboard_xt_init tests passed\n");
    return 0;
}
