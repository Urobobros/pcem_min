#ifndef MODULE_COMMON_H
#define MODULE_COMMON_H

#include "ibm.h"
#include "cpu.h"
#include "model.h"
#include "io.h"
#include "mouse.h"

#include "device.h"
#include "dma.h"
#include "fdc.h"
#include "fdc37c665.h"
#include "fdc37c93x.h"
#include "ide.h"
#include "keyboard_at.h"
#include "keyboard_olim24.h"
#include "keyboard_pcjr.h"
#include "keyboard_xt.h"
#include "mem.h"
#include "nmi.h"
#include "nvr.h"
#include "pci.h"
#include "pic.h"
#include "pit.h"
#include "scamp.h"
#include "serial.h"
#include "sio.h"
#include "superxt.h"
#include <pcem/devices.h>
void xt_init();
void pcjr_init();
void tandy1k_init();
void tandy1ksl2_init();
void at_init();
void ibm_at_init();
void at_sis496_init();
void compaq_xt_init();

#endif /* MODULE_COMMON_H */
