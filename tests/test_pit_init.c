#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "ibm.h"
#undef printf
#include "io.h"
#include "models/pit.h"

extern uint8_t pit_read(uint16_t, void *);
extern void pit_write(uint16_t, uint8_t, void *);
extern PIT pit;
extern uint8_t (*port_inb[0x10000][2])(uint16_t, void*);
extern void (*port_outb[0x10000][2])(uint16_t, uint8_t, void*);
extern void *port_priv[0x10000][2];

void pclog(const char *fmt, ...) {}
void error(const char *fmt, ...) {}
void fatal(const char *fmt, ...) {}
void warning(const char *fmt, ...) {}

uint8_t mem_readb_phys(uint32_t addr) { return 0; }
void mem_writeb_phys(uint32_t addr, uint8_t val) {}
void mem_invalidate_range(uint32_t start, uint32_t end) {}
int cpu_get_speed() { return 4770000; }
void speaker_update() {}
void picint(uint16_t num) {}
void picintc(uint16_t num) {}
void timer_process() {}
int nmi = 0;
int nmi_auto_clear = 0;
int speakon = 0;
int ppispeakon = 0;
int speakval = 0;
PPI ppi;
#include "private/timer.h"
void timer_add(pc_timer_t *timer, void (*callback)(void *), void *p, int start) { timer->callback = callback; timer->p = p; timer->enabled = start; }
uint32_t timer_target;
uint64_t TIMER_USEC;
void timer_enable(pc_timer_t *timer) { timer->enabled = 1; }
void timer_disable(pc_timer_t *timer) { timer->enabled = 0; }

void device_speed_changed() {}
void video_updatetiming() {}
uint64_t tsc = 0;
int cpu_busspeed = 1;
uint64_t xt_cpu_multi;
uint8_t _ram_storage[1];
uint8_t *ram = _ram_storage;

int main() {
    io_init();
    pit_init();
    for (int p = 0x40; p <= 0x43; p++) {
        assert(port_inb[p][0] == pit_read);
        assert(port_outb[p][0] == pit_write);
        assert(port_priv[p][0] == &pit);
    }

    printf("pit_init tests passed\n");
    return 0;
}
