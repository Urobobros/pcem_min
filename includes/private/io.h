#ifndef _IO_H_
#define _IO_H_

#include <stdint.h>

void io_init();

void io_sethandler_named(uint16_t base, int size, uint8_t (*inb)(uint16_t addr, void *priv),
                         uint16_t (*inw)(uint16_t addr, void *priv), uint32_t (*inl)(uint16_t addr, void *priv),
                         void (*outb)(uint16_t addr, uint8_t val, void *priv),
                         void (*outw)(uint16_t addr, uint16_t val, void *priv),
                         void (*outl)(uint16_t addr, uint32_t val, void *priv), void *priv, const char *inb_name,
                         const char *inw_name, const char *inl_name, const char *outb_name, const char *outw_name,
                         const char *outl_name);

#define io_sethandler(base, size, inb, inw, inl, outb, outw, outl, priv)                                                         \
        io_sethandler_named(base, size, inb, inw, inl, outb, outw, outl, priv, inb ? #inb : NULL, inw ? #inw : NULL,             \
                            inl ? #inl : NULL, outb ? #outb : NULL, outw ? #outw : NULL, outl ? #outl : NULL)

void io_removehandler(uint16_t base, int size, uint8_t (*inb)(uint16_t addr, void *priv),
                      uint16_t (*inw)(uint16_t addr, void *priv), uint32_t (*inl)(uint16_t addr, void *priv),
                      void (*outb)(uint16_t addr, uint8_t val, void *priv), void (*outw)(uint16_t addr, uint16_t val, void *priv),
                      void (*outl)(uint16_t addr, uint32_t val, void *priv), void *priv);

#endif /* _IO_H_ */
