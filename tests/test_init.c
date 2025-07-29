#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "ibm.h"
#undef printf
/* Stub logging */
#include "io.h"
#include "models/pit.h"
#include "models/dma.h"
extern uint8_t (*port_inb[0x10000][2])(uint16_t, void*);
extern void (*port_outb[0x10000][2])(uint16_t, uint8_t, void*);
extern void *port_priv[0x10000][2];
void pclog(const char *fmt, ...) {}
void error(const char *fmt, ...) {}
void fatal(const char *fmt, ...) {}
void warning(const char *fmt, ...) {}

/* Stub variables expected by headers */
uint8_t _ram_storage[1];
uint8_t *ram = _ram_storage;
uint64_t tsc = 0;
int cpu_busspeed = 1;
uint64_t xt_cpu_multi;

/* Timer stubs */
#include <string.h>
uint8_t mem_readb_phys(uint32_t addr) { return 0; }
void mem_writeb_phys(uint32_t addr, uint8_t val) {}
void mem_invalidate_range(uint32_t start, uint32_t end) {}
int cpu_get_speed() { return 4770000; }
void speaker_update() {}
void picint(uint16_t num) {}
void picintc(uint16_t num) {}
int nmi = 0;
int nmi_auto_clear = 0;
int speakon = 0;
void timer_process() {}
int ppispeakon = 0;
int speakval = 0;
PPI ppi;
#include "private/timer.h"
void timer_add(pc_timer_t *timer, void (*callback)(void *), void *p, int start) { timer->callback = callback; timer->p = p; timer->enabled = start; }
uint32_t timer_target;
uint64_t TIMER_USEC;
void timer_enable(pc_timer_t *timer) { timer->enabled = 1; }
void timer_disable(pc_timer_t *timer) { timer->enabled = 0; }

/* Stubs for other external dependencies */
void device_speed_changed() {}
void video_updatetiming() {}

int main() {
    io_init();
    pit_init();
    for (int p=0x40; p<=0x43; p++) {
        assert(port_inb[p][0] != NULL || port_outb[p][0] != NULL);
    }

    dma_init();
    assert(port_outb[0x00][0] != NULL || port_inb[0x00][0] != NULL);
    assert(port_outb[0x0f][0] != NULL || port_inb[0x0f][0] != NULL);
    assert(port_outb[0x80][0] != NULL || port_inb[0x80][0] != NULL);

    io_sethandler(0x1234, 1, NULL, NULL, NULL, NULL, NULL, NULL, (void*)0xdead);
    assert(port_priv[0x1234][0] == (void*)0xdead);

    printf("All tests passed\n");
    return 0;
}
