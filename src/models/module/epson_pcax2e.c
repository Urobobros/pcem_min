#include "module/common.h"

void epson_pcax2e_init() {
        at_init();
}

MODEL m_epson_pcax2e = {"[286] Epson PC AX2e",
                        ROM_EPSON_PCAX2E,
                        "epson_pcax2e",
                        {{"", cpus_286}, {"", NULL}, {"", NULL}},
                        MODEL_GFX_NONE | MODEL_AT | MODEL_PS2,
                        256,
                        15872,
                        128,
                        epson_pcax2e_init,
                        NULL};


