#include "ibm.h"
#include "ide.h"
#include "io.h"
#include "video.h"
#include "cpu.h"
#include <stdio.h>

#ifdef PORT_DEBUG
#include <pcem/portlog.h>
#define PORT_LOG(fmt, ...) portlog(fmt, __VA_ARGS__)
#else
#define PORT_LOG(fmt, ...)
#endif

#define COMBINE_NAMES(buf, name1, name2)                                                                                         \
        do {                                                                                                                     \
                if ((name1) && (name2))                                                                                          \
                        snprintf(buf, sizeof(buf), "%s/%s", name1, name2);                                                       \
                else if (name1)                                                                                                  \
                        snprintf(buf, sizeof(buf), "%s", name1);                                                                 \
                else if (name2)                                                                                                  \
                        snprintf(buf, sizeof(buf), "%s", name2);                                                                 \
                else                                                                                                             \
                        snprintf(buf, sizeof(buf), "unhandled");                                                                 \
        } while (0)

uint8_t (*port_inb[0x10000][2])(uint16_t addr, void *priv);
uint16_t (*port_inw[0x10000][2])(uint16_t addr, void *priv);
uint32_t (*port_inl[0x10000][2])(uint16_t addr, void *priv);

void (*port_outb[0x10000][2])(uint16_t addr, uint8_t val, void *priv);
void (*port_outw[0x10000][2])(uint16_t addr, uint16_t val, void *priv);
void (*port_outl[0x10000][2])(uint16_t addr, uint32_t val, void *priv);

const char *port_inb_name[0x10000][2];
const char *port_inw_name[0x10000][2];
const char *port_inl_name[0x10000][2];
const char *port_outb_name[0x10000][2];
const char *port_outw_name[0x10000][2];
const char *port_outl_name[0x10000][2];

void *port_priv[0x10000][2];

void io_init() {
        int c;
        pclog("io_init\n");
        for (c = 0; c < 0x10000; c++) {
                port_inb[c][0] = NULL;
                port_inb_name[c][0] = NULL;
                port_inw[c][0] = NULL;
                port_inw_name[c][0] = NULL;
                port_inl[c][0] = NULL;
                port_inl_name[c][0] = NULL;
                port_outb[c][0] = NULL;
                port_outb_name[c][0] = NULL;
                port_outw[c][0] = NULL;
                port_outw_name[c][0] = NULL;
                port_outl[c][0] = NULL;
                port_outl_name[c][0] = NULL;

                port_inb[c][1] = NULL;
                port_inb_name[c][1] = NULL;
                port_inw[c][1] = NULL;
                port_inw_name[c][1] = NULL;
                port_inl[c][1] = NULL;
                port_inl_name[c][1] = NULL;
                port_outb[c][1] = NULL;
                port_outb_name[c][1] = NULL;
                port_outw[c][1] = NULL;
                port_outw_name[c][1] = NULL;
                port_outl[c][1] = NULL;
                port_outl_name[c][1] = NULL;

                port_priv[c][0] = NULL;
                port_priv[c][1] = NULL;
        }
}

void io_sethandler_named(uint16_t base, int size, uint8_t (*inb)(uint16_t addr, void *priv),
                         uint16_t (*inw)(uint16_t addr, void *priv), uint32_t (*inl)(uint16_t addr, void *priv),
                         void (*outb)(uint16_t addr, uint8_t val, void *priv),
                         void (*outw)(uint16_t addr, uint16_t val, void *priv),
                         void (*outl)(uint16_t addr, uint32_t val, void *priv), void *priv, const char *inb_name,
                         const char *inw_name, const char *inl_name, const char *outb_name, const char *outw_name,
                         const char *outl_name) {
        int c;
        for (c = 0; c < size; c++) {
                if (!port_inb[base + c][0] && !port_inw[base + c][0] && !port_inl[base + c][0] && !port_outb[base + c][0] &&
                    !port_outw[base + c][0] && !port_outl[base + c][0]) {
                        port_inb[base + c][0] = inb;
                        port_inw[base + c][0] = inw;
                        port_inl[base + c][0] = inl;
                        port_outb[base + c][0] = outb;
                        port_outw[base + c][0] = outw;
                        port_outl[base + c][0] = outl;
                        port_inb_name[base + c][0] = inb_name;
                        port_inw_name[base + c][0] = inw_name;
                        port_inl_name[base + c][0] = inl_name;
                        port_outb_name[base + c][0] = outb_name;
                        port_outw_name[base + c][0] = outw_name;
                        port_outl_name[base + c][0] = outl_name;
                        port_priv[base + c][0] = priv;
                } else if (!port_inb[base + c][1] && !port_inw[base + c][1] && !port_inl[base + c][1] &&
                           !port_outb[base + c][1] && !port_outw[base + c][1] && !port_outl[base + c][1]) {
                        port_inb[base + c][1] = inb;
                        port_inw[base + c][1] = inw;
                        port_inl[base + c][1] = inl;
                        port_outb[base + c][1] = outb;
                        port_outw[base + c][1] = outw;
                        port_outl[base + c][1] = outl;
                        port_inb_name[base + c][1] = inb_name;
                        port_inw_name[base + c][1] = inw_name;
                        port_inl_name[base + c][1] = inl_name;
                        port_outb_name[base + c][1] = outb_name;
                        port_outw_name[base + c][1] = outw_name;
                        port_outl_name[base + c][1] = outl_name;
                        port_priv[base + c][1] = priv;
                }
        }
}

void io_removehandler(uint16_t base, int size, uint8_t (*inb)(uint16_t addr, void *priv),
                      uint16_t (*inw)(uint16_t addr, void *priv), uint32_t (*inl)(uint16_t addr, void *priv),
                      void (*outb)(uint16_t addr, uint8_t val, void *priv), void (*outw)(uint16_t addr, uint16_t val, void *priv),
                      void (*outl)(uint16_t addr, uint32_t val, void *priv), void *priv) {
        int c;
        for (c = 0; c < size; c++) {
                if (port_priv[base + c][0] == priv && port_inb[base + c][0] == inb && port_inw[base + c][0] == inw &&
                    port_inl[base + c][0] == inl && port_outb[base + c][0] == outb && port_outw[base + c][0] == outw &&
                    port_outl[base + c][0] == outl) {
                        port_inb[base + c][0] = NULL;
                        port_inb_name[base + c][0] = NULL;
                        port_inw[base + c][0] = NULL;
                        port_inw_name[base + c][0] = NULL;
                        port_inl[base + c][0] = NULL;
                        port_inl_name[base + c][0] = NULL;
                        port_outb[base + c][0] = NULL;
                        port_outb_name[base + c][0] = NULL;
                        port_outw[base + c][0] = NULL;
                        port_outw_name[base + c][0] = NULL;
                        port_outl[base + c][0] = NULL;
                        port_outl_name[base + c][0] = NULL;
                        port_priv[base + c][0] = NULL;
                }
                if (port_priv[base + c][1] == priv && port_inb[base + c][1] == inb && port_inw[base + c][1] == inw &&
                    port_inl[base + c][1] == inl && port_outb[base + c][1] == outb && port_outw[base + c][1] == outw &&
                    port_outl[base + c][1] == outl) {
                        port_inb[base + c][1] = NULL;
                        port_inb_name[base + c][1] = NULL;
                        port_inw[base + c][1] = NULL;
                        port_inw_name[base + c][1] = NULL;
                        port_inl[base + c][1] = NULL;
                        port_inl_name[base + c][1] = NULL;
                        port_outb[base + c][1] = NULL;
                        port_outb_name[base + c][1] = NULL;
                        port_outw[base + c][1] = NULL;
                        port_outw_name[base + c][1] = NULL;
                        port_outl[base + c][1] = NULL;
                        port_outl_name[base + c][1] = NULL;
                        port_priv[base + c][1] = NULL;
                }
        }
}

uint8_t cgamode, cgastat = 0, cgacol;
int hsync;
uint8_t lpt2dat;
int sw9;
int t237 = 0;

uint8_t inb(uint16_t port) {
        uint8_t temp = 0xff;

        if (port_inb[port][0])
                temp &= port_inb[port][0](port, port_priv[port][0]);
        if (port_inb[port][1])
                temp &= port_inb[port][1](port, port_priv[port][1]);

        char nbuf[64];
        COMBINE_NAMES(nbuf, port_inb_name[port][0], port_inb_name[port][1]);
        PORT_LOG("IN  port 0x%04X, size 1, value 0x%02X  # %s\n", port, temp, nbuf);

        /*           if (!port_inb[port][0] && !port_inb[port][1])
                        pclog("Bad INB %04X %04X:%04X\n", port, CS, pc);*/

        return temp;
}

uint8_t cpu_readport(uint32_t port) { return inb(port); }

void outb(uint16_t port, uint8_t val) {
        char nbuf[64];
        COMBINE_NAMES(nbuf, port_outb_name[port][0], port_outb_name[port][1]);
        PORT_LOG("OUT port 0x%04X, size 1, value 0x%02X  # %s\n", port, val, nbuf);
        if (port_outb[port][0])
                port_outb[port][0](port, val, port_priv[port][0]);
        if (port_outb[port][1])
                port_outb[port][1](port, val, port_priv[port][1]);

        /*        if (!port_outb[port][0] && !port_outb[port][1])
                        pclog("Bad OUTB %04X %02X %04X:%08X\n", port, val, CS, pc);*/
        return;
}

uint16_t inw(uint16_t port) {
        //        pclog("INW %04X\n", port);
        uint16_t val;
        if (port_inw[port][0])
                val = port_inw[port][0](port, port_priv[port][0]);
        else if (port_inw[port][1])
                val = port_inw[port][1](port, port_priv[port][1]);
        else
                val = inb(port) | (inb(port + 1) << 8);

        char nbuf[64];
        COMBINE_NAMES(nbuf, port_inw_name[port][0], port_inw_name[port][1]);
        PORT_LOG("IN  port 0x%04X, size 2, value 0x%04X  # %s\n", port, val, nbuf);

        return val;
}

void outw(uint16_t port, uint16_t val) {
        //        printf("OUTW %04X %04X %04X:%08X\n",port,val, CS, pc);
        /*        if ((port & ~0xf) == 0xf000)
                   pclog("OUTW %04X %04X\n", port, val);*/

        char nbuf[64];
        COMBINE_NAMES(nbuf, port_outw_name[port][0], port_outw_name[port][1]);
        PORT_LOG("OUT port 0x%04X, size 2, value 0x%04X  # %s\n", port, val, nbuf);

        if (port_outw[port][0])
                port_outw[port][0](port, val, port_priv[port][0]);
        if (port_outw[port][1])
                port_outw[port][1](port, val, port_priv[port][1]);

        if (port_outw[port][0] || port_outw[port][1])
                return;

        outb(port, val);
        outb(port + 1, val >> 8);
}

uint32_t inl(uint16_t port) {
        //        pclog("INL %04X\n", port);
        uint32_t val;
        if (port_inl[port][0])
                val = port_inl[port][0](port, port_priv[port][0]);
        else if (port_inl[port][1])
                val = port_inl[port][1](port, port_priv[port][1]);
        else
                val = inw(port) | (inw(port + 2) << 16);

        char nbuf[64];
        COMBINE_NAMES(nbuf, port_inl_name[port][0], port_inl_name[port][1]);
        PORT_LOG("IN  port 0x%04X, size 4, value 0x%08X  # %s\n", port, val, nbuf);

        return val;
}

void outl(uint16_t port, uint32_t val) {
        /*        if ((port & ~0xf) == 0xf000)
                   pclog("OUTL %04X %08X\n", port, val);*/

        char nbuf[64];
        COMBINE_NAMES(nbuf, port_outl_name[port][0], port_outl_name[port][1]);
        PORT_LOG("OUT port 0x%04X, size 4, value 0x%08X  # %s\n", port, val, nbuf);

        if (port_outl[port][0])
                port_outl[port][0](port, val, port_priv[port][0]);
        if (port_outl[port][1])
                port_outl[port][1](port, val, port_priv[port][1]);

        if (port_outl[port][0] || port_outl[port][1])
                return;

        outw(port, val);
        outw(port + 2, val >> 16);
}
