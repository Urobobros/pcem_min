#include "ibm.h"
#include "io.h"
#include "keyboard.h"

static uint8_t keyboard_none_read(uint16_t port, void *priv) {
        /* Return 0xff to indicate no device */
        return 0xff;
}

static void keyboard_none_write(uint16_t port, uint8_t val, void *priv) {
        /* Ignore writes */
        (void)port;
        (void)val;
        (void)priv;
}

void keyboard_none_poll() { /* Nothing to do */ }

void keyboard_none_init() {
        /* Install dummy handlers on typical keyboard ports */
        io_sethandler(0x0060, 0x0005, keyboard_none_read, NULL, NULL, keyboard_none_write, NULL, NULL, NULL);
        io_sethandler(0x00a0, 0x0008, keyboard_none_read, NULL, NULL, keyboard_none_write, NULL, NULL, NULL);
        keyboard_send = keyboard_none_write;
        keyboard_poll = keyboard_none_poll;
        keyboard_scan = 0;
}
