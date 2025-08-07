#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "ibm.h"
#undef printf
#include "io.h"
#include "models/dma.h"

extern uint8_t (*port_inb[0x10000][2])(uint16_t, void*);
extern void (*port_outb[0x10000][2])(uint16_t, uint8_t, void*);
extern void *port_priv[0x10000][2];

/* Explicit declarations of handlers to compare pointers */
extern uint8_t dma_read(uint16_t, void *);
extern void dma_write(uint16_t, uint8_t, void *);
extern uint8_t dma_page_read(uint16_t, void *);
extern void dma_page_write(uint16_t, uint8_t, void *);

void pclog(const char *fmt, ...) {}
void error(const char *fmt, ...) {}
void fatal(const char *fmt, ...) {}
void warning(const char *fmt, ...) {}

uint8_t mem_readb_phys(uint32_t addr) { return 0; }
void mem_writeb_phys(uint32_t addr, uint8_t val) {}
void mem_invalidate_range(uint32_t start, uint32_t end) {}

int main() {
    io_init();
    dma_init();

    for (int p = 0x00; p < 0x10; p++) {
        assert(port_inb[p][0] == dma_read);
        assert(port_outb[p][0] == dma_write);
        assert(port_priv[p][0] == NULL);
    }

    for (int p = 0x80; p < 0x88; p++) {
        assert(port_inb[p][0] == dma_page_read);
        assert(port_outb[p][0] == dma_page_write);
        assert(port_priv[p][0] == NULL);
    }

    printf("dma_init tests passed\n");
    return 0;
}
