#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "ibm.h"
#undef printf
#include "io.h"
#include "models/pic.h"

extern uint8_t (*port_inb[0x10000][2])(uint16_t, void*);
extern void (*port_outb[0x10000][2])(uint16_t, uint8_t, void*);

void pclog(const char *fmt, ...) {}
void error(const char *fmt, ...) {}
void fatal(const char *fmt, ...) {}
void warning(const char *fmt, ...) {}

int main() {
    io_init();
    pic_init();
    pic2_init();

    for (int p = 0x20; p <= 0x21; p++) {
        assert(port_inb[p][0] != NULL);
        assert(port_outb[p][0] != NULL);
    }
    for (int p = 0xA0; p <= 0xA1; p++) {
        assert(port_inb[p][0] != NULL);
        assert(port_outb[p][0] != NULL);
    }

    printf("pic_init tests passed\n");
    return 0;
}
