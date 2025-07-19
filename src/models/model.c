#include "ibm.h"
#include "cpu.h"
#include "model.h"
#include "dma.h"
#include "fdc.h"
#include "lpt.h"
#include "pic.h"
#include "pit.h"
#include "serial.h"
#include "keyboard_xt.h"
#include "nmi.h"
#include "gameport.h"
#include "cassette.h"
#include "mem.h"
#include "ide.h"
#include <pcem/devices.h>

int AMSTRAD, AT, PCI, TANDY, MCA;

static void common_init() {
    dma_init();
    fdc_add();
    lpt_init();
    pic_init();
    pit_init();
    serial1_init(0x3f8, 4, 1);
    serial2_init(0x2f8, 3, 1);
}

static void xt_init() {
    common_init();
    mem_add_bios();
    pit_set_out_func(&pit, 1, pit_refresh_timer_xt);
    keyboard_xt_init();
    nmi_init();
    device_add(&gameport_device);
    if (romset == ROM_IBMPC)
        device_add(&cassette_device);
}

static MODEL m_genxt = {
    "[8088] Generic XT clone",
    ROM_GENXT,
    "genxt",
    {{"", cpus_8088}, {"", NULL}, {"", NULL}},
    MODEL_GFX_NONE,
    32,
    704,
    16,
    xt_init,
    NULL};

MODEL *models[ROM_MAX];
int model;

int model_getromset() { return models[model]->id; }
int model_getromset_from_model(int m) { return models[m]->id; }
int model_getmodel(int romset) {
    int c = 0;
    while (models[c]) {
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
    while (models[c]) {
        if (!strcmp(models[c]->internal_name, s))
            return c;
        c++;
    }
    return 0;
}
int model_has_fixed_gfx(int m) {
    int flags = models[m]->flags & MODEL_GFX_MASK;
    return flags == MODEL_GFX_FIXED;
}
int model_has_optional_gfx(int m) {
    int flags = models[m]->flags & MODEL_GFX_MASK;
    return flags == MODEL_GFX_DISABLE_HW || flags == MODEL_GFX_DISABLE_SW;
}

void model_init() {
    pclog("Initting as %s\n", model_getname());
    AMSTRAD = AT = PCI = TANDY = MCA = 0;
    ide_set_bus_master(NULL, NULL, NULL, NULL);
    models[model]->init();
    if (models[model]->device)
        device_add(models[model]->device);
}

void model_init_builtin() {
    pcem_add_model(&m_genxt);
}
