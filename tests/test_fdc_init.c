#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "ibm.h"
#undef printf
#include "io.h"
#include "floppy/fdc.h"

extern uint8_t fdc_read(uint16_t, void *);
extern void fdc_write(uint16_t, uint8_t, void *);
extern uint8_t (*port_inb[0x10000][2])(uint16_t, void*);
extern void (*port_outb[0x10000][2])(uint16_t, uint8_t, void*);

uint8_t mem_readb_phys(uint32_t addr) { return 0; }
void mem_writeb_phys(uint32_t addr, uint8_t val) {}
void mem_invalidate_range(uint32_t start, uint32_t end) {}

/* Timer stubs matching fdc.c expectations */
uint64_t tsc = 0;
int cpu_busspeed = 1;
uint64_t xt_cpu_multi;
#include "private/timer.h"
void timer_add(pc_timer_t *timer, void (*callback)(void *), void *p, int start) { timer->callback = callback; timer->p = p; timer->enabled = start; }
uint32_t timer_target; uint64_t TIMER_USEC; void timer_enable(pc_timer_t *timer) { timer->enabled = 1; } void timer_disable(pc_timer_t *timer) { timer->enabled = 0; }
void picint(uint16_t num) {}
void picintc(uint16_t num) {}

void pclog(const char *fmt, ...) {}
void error(const char *fmt, ...) {}
void fatal(const char *fmt, ...) {}
void warning(const char *fmt, ...) {}

int main() {
    io_init();
    fdc_add();

    for (int p = 0x3f0; p <= 0x3f5; p++) {
        assert(port_inb[p][0] == fdc_read);
        assert(port_outb[p][0] == fdc_write);
    }
    assert(port_inb[0x3f7][0] == fdc_read);
    assert(port_outb[0x3f7][0] == fdc_write);

    printf("fdc_add tests passed\n");
    return 0;
}
