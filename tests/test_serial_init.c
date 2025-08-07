#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "ibm.h"
#undef printf
#include "io.h"
#include "models/serial.h"

extern uint8_t serial_read(uint16_t, void *);
extern void serial_write(uint16_t, uint8_t, void *);
extern SERIAL serial1, serial2;
extern uint8_t (*port_inb[0x10000][2])(uint16_t, void*);
extern void (*port_outb[0x10000][2])(uint16_t, uint8_t, void*);
extern void *port_priv[0x10000][2];

void pclog(const char *fmt, ...) {}
void error(const char *fmt, ...) {}
void fatal(const char *fmt, ...) {}
void warning(const char *fmt, ...) {}
void picintlevel(int level) {}
void picintc(uint16_t num) {}

uint8_t mem_readb_phys(uint32_t addr) { return 0; }
void mem_writeb_phys(uint32_t addr, uint8_t val) {}
void mem_invalidate_range(uint32_t start, uint32_t end) {}

uint64_t tsc = 0;
int cpu_busspeed = 1;
uint64_t xt_cpu_multi;

#include "private/timer.h"
void timer_add(pc_timer_t *timer, void (*callback)(void *), void *p, int start) { timer->callback = callback; timer->p = p; timer->enabled = start; }
uint32_t timer_target; uint64_t TIMER_USEC; void timer_enable(pc_timer_t *timer) { timer->enabled = 1; } void timer_disable(pc_timer_t *timer) { timer->enabled = 0; }

int main() {
    io_init();
    serial1_init(0x3f8, 4, 1);
    serial2_init(0x2f8, 3, 1);

    for (int p = 0x3f8; p < 0x400; p++) {
        assert(port_inb[p][0] == serial_read);
        assert(port_outb[p][0] == serial_write);
        assert(port_priv[p][0] == &serial1);
    }

    for (int p = 0x2f8; p < 0x300; p++) {
        assert(port_inb[p][0] == serial_read);
        assert(port_outb[p][0] == serial_write);
        assert(port_priv[p][0] == &serial2);
    }

    printf("serial init tests passed\n");
    return 0;
}
