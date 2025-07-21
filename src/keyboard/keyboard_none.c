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

static void keyboard_none_send(uint8_t val) {
        (void)val;
}

void keyboard_none_poll() { /* Nothing to do */ }

void keyboard_none_init() {
        /* Remove any existing handlers for keyboard ports so the device appears absent */
        io_removehandler(0x0060, 0x0005, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        io_removehandler(0x00a0, 0x0008, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

        /* Use stub callbacks so keyboard events are ignored */
        keyboard_send = keyboard_none_send;
        keyboard_poll = keyboard_none_poll;
        keyboard_scan = 0;
}
