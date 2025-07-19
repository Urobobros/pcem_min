#include "ibm.h"
#include "cpu.h"
#include "model.h"
#include "io.h"
#include "mouse.h"

#include "82091aa.h"
#include "acc2168.h"
#include "acc3221.h"
#include "acer386sx.h"
#include "ali1429.h"
#include "cbm_io.h"
#include "cmd640.h"
#include "compaq.h"
#include "cs8230.h"
#include "dells200.h"
#include "device.h"
#include "cassette.h"
#include "dma.h"
#include "f82c710_upc.h"
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
#include "lpt.h"
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
#include "vid_pcjr.h"
#include "vid_tandy.h"
#include "vid_t1000.h"
#include <pcem/devices.h>

void xt_init();
void pcjr_init();
void tandy1k_init();
void tandy1ksl2_init();
void at_init();
void ibm_at_init();
void at_sis496_init();
void compaq_xt_init();

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
        lpt_init();
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

void compaq_xt_init() {
        xt_init();
        lpt1_remove();
        lpt2_remove();
        lpt1_init(0x3bc);
}

void pcjr_init() {
        mem_add_bios();
        fdc_add_pcjr();
        pic_init();
        pit_init();
        pit_set_out_func(&pit, 0, pit_irq0_timer_pcjr);
        serial1_init(0x2f8, 3, 1);
        keyboard_pcjr_init();
        device_add(&sn76489_device);
        nmi_mask = 0x80;
        device_add(&cassette_device);
}

void tandy1k_init() {
        TANDY = 1;
        common_init();
        mem_add_bios();
        keyboard_tandy_init();
        if (romset == ROM_TANDY)
                device_add(&sn76489_device);
        else
                device_add(&ncr8496_device);
        nmi_init();
        if (romset != ROM_TANDY)
                device_add(&tandy_eeprom_device);
        device_add(&gameport_device);
}
void tandy1ksl2_init() {
        //        TANDY = 1;
        common_init();
        mem_add_bios();
        keyboard_tandy_init();
        device_add(&pssj_device);
        nmi_init();
        device_add(&tandy_rom_device);
        device_add(&tandy_eeprom_device);
        device_add(&gameport_device);
}



void at_init() {
        AT = 1;
        common_init();
        mem_add_bios();
        pit_set_out_func(&pit, 1, pit_refresh_timer_at);
        dma16_init();
        keyboard_at_init();
        device_add(&nvr_device);
        pic2_init();
        device_add(&gameport_device);
        nmi_mask = 0;
}

void ibm_at_init() {
        at_init();
        mem_remap_top_384k();
}

void ps1_common_init() {
        AT = 1;
        common_init();
        mem_add_bios();
        pit_set_out_func(&pit, 1, pit_refresh_timer_at);
        dma16_init();
        keyboard_at_init();
        device_add(&nvr_device);
        pic2_init();
        fdc_set_dskchg_activelow();
        device_add(&ps1_audio_device);
        /*PS/1 audio uses ports 200h and 202-207h, so only initialise gameport on 201h*/
        device_add(&gameport_201_device);
}


static void ps2_common_init() {
        AT = 1;
        common_init();
        mem_add_bios();
        dma16_init();
        ps2_dma_init();
        keyboard_at_init();
        keyboard_at_init_ps2();
        //        mouse_ps2_init();
        device_add(&nvr_device);
        pic2_init();

        pit_ps2_init();

        nmi_mask = 0x80;
}

void at_sis496_init() {
        at_init();
        pci_init(PCI_CONFIG_TYPE_1);
        pci_slot(0xb);
        pci_slot(0xd);
        pci_slot(0xf);
        device_add(&sis496_device);
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
MODEL m_amixt = {"[8088] AMI XT clone",
                 ROM_AMIXT,
                 "amixt",
                 {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                 MODEL_GFX_NONE,
                 64,
                 640,
                 64,
                 xt_init,
                 NULL};
MODEL m_ataripc3 = {"[8088] Atari PC3",
                    ROM_ATARIPC3,
                    "ataripc3",
                    {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                    MODEL_GFX_NONE,
                    64,
                    640,
                    64,
                    xt_init,
                    NULL};
MODEL m_cbm_pc10 = {"[8088] Commodore PC-10",
                    ROM_CBM_PC10,
                    "cbm_pc10",
                    {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                    MODEL_GFX_NONE,
                    640,
                    640,
                    64,
                    xt_init,
                    NULL};
MODEL m_compaq_pip = {"[8088] Compaq Portable Plus",
                      ROM_COMPAQ_PIP,
                      "compaq_pip",
                      {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                      MODEL_GFX_NONE,
                      128,
                      640,
                      64,
                      compaq_xt_init,
                      NULL};
MODEL m_dtk = {"[8088] DTK XT clone",
               ROM_DTKXT,
               "dtk",
               {{"", cpus_8088}, {"", NULL}, {"", NULL}},
               MODEL_GFX_NONE,
               64,
               640,
               64,
               xt_init,
               NULL};
MODEL m_genxt = {"[8088] Generic XT clone",
                 ROM_GENXT,
                 "genxt",
                 {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                 MODEL_GFX_NONE,
                 32,
                 704,
                 16,
                 xt_init,
                 NULL};
MODEL m_super16t = {"[8088] Hyundai Super16T",
                     ROM_HYUNDAI_SUPER16T,
                     "super16t",
                     {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                     MODEL_GFX_NONE,
                     640,
                     640,
                     64,
                     xt_init,
                     NULL};
MODEL m_super16te = {"[8088] Hyundai Super16TE",
                      ROM_HYUNDAI_SUPER16TE,
                      "super16te",
                      {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                      MODEL_GFX_NONE,
                      640,
                      640,
                      64,
                      xt_init,
                      NULL};
MODEL m_ibmpc = {"[8088] IBM PC", ROM_IBMPC, "ibmpc", {{"", cpus_8088}, {"", NULL}, {"", NULL}}, MODEL_GFX_NONE, 64, 640, 32,
                 xt_init,         NULL};
MODEL m_ibmpcjr = {"[8088] IBM PCjr", ROM_IBMPCJR, "ibmpcjr", {{"", cpus_pcjr}, {"", NULL}, {"", NULL}},
                   MODEL_GFX_FIXED,   128,         640,       64,
                   pcjr_init,         &pcjr_device};
MODEL m_ibmxt = {"[8088] IBM XT", ROM_IBMXT, "ibmxt", {{"", cpus_8088}, {"", NULL}, {"", NULL}}, MODEL_GFX_NONE, 64, 640, 64,
                 xt_init,         NULL};
MODEL m_jukopc = {"[8088] Juko XT clone",
                  ROM_JUKOPC,
                  "jukopc",
                  {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                  MODEL_GFX_NONE,
                  64,
                  640,
                  64,
                  xt_init,
                  NULL};
MODEL m_ledge_modelm = {"[8088] Leading Edge Model M",
                        ROM_LEDGE_MODELM,
                        "ledge_modelm",
                        {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                        MODEL_GFX_NONE,
                        128,
                        704,
                        64,
                        xt_init,
                        NULL};
MODEL m_ncr_pc4i = {"[8088] NCR PC4i", ROM_NCR_PC4I, "ncr_pc4i", {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                    MODEL_GFX_NONE,    256,          640,        64,
                    xt_init,           NULL};
MODEL m_pxxt = {"[8088] Phoenix XT clone",
                ROM_PXXT,
                "pxxt",
                {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                MODEL_GFX_NONE,
                64,
                640,
                64,
                xt_init,
                NULL};
MODEL m_tandy = {
        "[8088] Tandy 1000", ROM_TANDY,        "tandy", {{"", cpus_8088}, {"", NULL}, {"", NULL}}, MODEL_GFX_FIXED, 128, 640, 128,
        tandy1k_init,        &tandy1000_device};
MODEL m_tandy1000hx = {"[8088] Tandy 1000 HX",
                       ROM_TANDY1000HX,
                       "tandy1000hx",
                       {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                       MODEL_GFX_FIXED,
                       256,
                       640,
                       128,
                       tandy1k_init,
                       &tandy1000hx_device};
MODEL m_to16_pc = {"[8088] Thomson TO16 PC",
                   ROM_TO16_PC,
                   "to16_pc",
                   {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                   MODEL_GFX_NONE,
                   512,
                   640,
                   128,
                   xt_init,
                   NULL};

MODEL m_deskpro = {"[8086] Compaq Deskpro", ROM_DESKPRO, "deskpro", {{"", cpus_8086}, {"", NULL}, {"", NULL}},
                   MODEL_GFX_NONE,          128,         640,       128,
                   compaq_xt_init,          NULL};
MODEL m_tandy1000sl2 = {"[8086] Tandy 1000 SL/2",
                        ROM_TANDY1000SL2,
                        "tandy1000sl2",
                        {{"", cpus_8086}, {"", NULL}, {"", NULL}},
                        MODEL_GFX_FIXED,
                        512,
                        768,
                        128,
                        tandy1ksl2_init,
                        NULL};
/* 286 PC's */


MODEL m_bull_micral_45 = {"[286] Bull Micral 45",
                          ROM_BULL_MICRAL_45,
                          "bull_micral_45",
                          {{"", cpus_286}, {"", NULL}, {"", NULL}},
                          MODEL_GFX_NONE | MODEL_AT | MODEL_HAS_IDE,
                          1024,
                          6144,
                          128,
                          ibm_at_init,
                          NULL};
MODEL m_compaq_pii = {"[286] Compaq Portable II",
                      ROM_COMPAQ_PII,
                      "compaq_pii",
                      {{"", cpus_286}, {"", NULL}, {"", NULL}},
                      MODEL_GFX_NONE | MODEL_AT | MODEL_HAS_IDE,
                      256,
                      15872,
                      128,
                      ibm_at_init,
                      NULL};
MODEL m_epson_pcax = {"[286] Epson PC AX",
                      ROM_EPSON_PCAX,
                      "epson_pcax",
                      {{"", cpus_286}, {"", NULL}, {"", NULL}},
                      MODEL_GFX_NONE | MODEL_AT,
                      256,
                      15872,
                      128,
                      at_init,
                      NULL};
MODEL m_epson_pcax2e = {"[286] Epson PC AX2e",
                        ROM_EPSON_PCAX2E,
                        "epson_pcax2e",
                        {{"", cpus_286}, {"", NULL}, {"", NULL}},
                        MODEL_GFX_NONE | MODEL_AT | MODEL_PS2,
                        256,
                        15872,
                        128,
                        at_init,
                        NULL};


MODEL m_ibmat = {"[286] IBM AT",
                 ROM_IBMAT,
                 "ibmat",
                 {{"", cpus_ibmat}, {"", NULL}, {"", NULL}},
                 MODEL_GFX_NONE | MODEL_AT,
                 256,
                 15872,
                 128,
                 ibm_at_init,
                 NULL};
MODEL m_ibmxt286 = {"[286] IBM XT Model 286",
                    ROM_IBMXT286,
                    "ibmxt286",
                    {{"", cpus_ibmxt286}, {"", NULL}, {"", NULL}},
                    MODEL_GFX_NONE | MODEL_AT,
                    256,
                    15872,
                    128,
                    ibm_at_init,
                    NULL};

MODEL m_tulip_tc7 = {"[286] Tulip AT Compact",
                     ROM_TULIP_TC7,
                     "tulip_tc7",
                     {{"", cpus_286}, {"", NULL}, {"", NULL}},
                     MODEL_GFX_NONE | MODEL_AT | MODEL_HAS_IDE,
                     640,
                     15872,
                     128,
                     ibm_at_init,
                     NULL};



MODEL m_epson_pcax3 = {"[386SX] Epson PC AX3",
                       ROM_EPSON_PCAX3,
                       "epson_pcax3",
                       {{"Intel", cpus_i386SX}, {"AMD", cpus_Am386SX}, {"Cyrix", cpus_486SLC}},
                       MODEL_GFX_NONE | MODEL_AT,
                       256,
                       15872,
                       128,
                       at_init,
                       NULL};



/* 486 PC's */
MODEL m_sis496 = {"[486] Award SiS 496/497",
                  ROM_SIS496,
                  "sis496",
                  {{"Intel", cpus_i486}, {"AMD", cpus_Am486}, {"Cyrix", cpus_Cx486}},
                  MODEL_GFX_NONE | MODEL_AT | MODEL_PCI | MODEL_HAS_IDE,
                  1,
                  256,
                  1,
                  at_sis496_init,
                  NULL};





void model_init_builtin() {
        /* 8088 PC's */
        pcem_add_model(&m_amixt);
        pcem_add_model(&m_ataripc3);
        pcem_add_model(&m_cbm_pc10);
        pcem_add_model(&m_compaq_pip);
        pcem_add_model(&m_dtk);
        pcem_add_model(&m_genxt);
        pcem_add_model(&m_super16t);
        pcem_add_model(&m_super16te);
        pcem_add_model(&m_ibmpc);
        pcem_add_model(&m_ibmpcjr);
        pcem_add_model(&m_ibmxt);
        pcem_add_model(&m_jukopc);
        pcem_add_model(&m_ledge_modelm);
        pcem_add_model(&m_ncr_pc4i);
        pcem_add_model(&m_pxxt);
        pcem_add_model(&m_tandy);
        pcem_add_model(&m_tandy1000hx);
        pcem_add_model(&m_to16_pc);

        /* 8086 PC's */
        pcem_add_model(&m_deskpro);
        pcem_add_model(&m_tandy1000sl2);

        /* 286 PC's */
        pcem_add_model(&m_bull_micral_45);
        pcem_add_model(&m_compaq_pii);
        pcem_add_model(&m_epson_pcax);
        pcem_add_model(&m_epson_pcax2e);
        pcem_add_model(&m_ibmat);
        pcem_add_model(&m_ibmxt286);
        pcem_add_model(&m_tulip_tc7);

        /* 386SX PC's */
        pcem_add_model(&m_epson_pcax3);

        /* 486 PC's */
        pcem_add_model(&m_sis496);
}