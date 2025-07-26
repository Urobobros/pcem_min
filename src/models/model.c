#include "ibm.h"
#include "cpu.h"
#include "model.h"
#include "io.h"
#include "mouse.h"

#include "device.h"
#include "cassette.h"
#include "dma.h"
#include "fdc.h"
#include "fdc37c665.h"
#include "fdc37c93x.h"
#include "gameport.h"
#include "ide.h"
#include "intel_flash.h"
#include "keyboard_at.h"
#include "keyboard_olim24.h"
#include "keyboard_pcjr.h"
#include "keyboard_xt.h"
#include "mem.h"
#include "mouse_ps2.h"
#include "nmi.h"
#include "nvr.h"
#include "pci.h"
#include "pic.h"
#include "pit.h"
#include "scamp.h"
#include "serial.h"
#include "sio.h"
#include "sis496.h"
#include "sl82c460.h"
#include "sound_ps1.h"
#include "sound_pssj.h"
#include "sound_sn76489.h"
#include "superxt.h"
#include "sst39sf010.h"
#include "tandy_eeprom.h"
#include "tandy_rom.h"
#include <pcem/devices.h>

void xt_init();

extern MODEL m_amixt;
int AMSTRAD, AT, PCI, TANDY, MCA;

int model_getromset() { return models[model]->id; }

int model_getromset_from_model(int model) { return models[model]->id; }

int model_getmodel(int romset) {
        int c = 0;

        while (models[c]->id != -1) {
                if (models[c]->id == romset)
                        return c;
                c++;
        }

        return 0;
}

char *model_getname() { return models[model]->name; }

char *model_get_internal_name() { return models[model]->internal_name; }

int model_get_model_from_internal_name(char *s) {
        int c = 0;

        while (models[c] != NULL) {
                if (!strcmp(models[c]->internal_name, s))
                        return c;
                c++;
        }

        return 0;
}

int model_has_fixed_gfx(int model) {
        int gfx_flags = models[model]->flags & MODEL_GFX_MASK;

        return (gfx_flags == MODEL_GFX_FIXED);
}

int model_has_optional_gfx(int model) {
        int gfx_flags = models[model]->flags & MODEL_GFX_MASK;

        return (gfx_flags == MODEL_GFX_DISABLE_HW || gfx_flags == MODEL_GFX_DISABLE_SW);
}

void common_init() {
        dma_init();
        fdc_add();
        pic_init();
        pit_init();
        serial1_init(0x3f8, 4, 1);
        serial2_init(0x2f8, 3, 1);
}

void xt_init() {
        common_init();
        mem_add_bios();
        pit_set_out_func(&pit, 1, pit_refresh_timer_xt);
        keyboard_xt_init();
        nmi_init();
        device_add(&gameport_device);
        if (romset == ROM_IBMPC)
                device_add(&cassette_device);
}

void model_init() {
        pclog("Initting as %s\n", model_getname());
        AMSTRAD = AT = PCI = TANDY = MCA = 0;
        ide_set_bus_master(NULL, NULL, NULL, NULL);

        models[model]->init();
        if (models[model]->device)
                device_add(models[model]->device);
}

/* 8088 PC's */
void model_init_builtin() {
        /* 8088 PC's */
        pcem_add_model(&m_amixt);
}
