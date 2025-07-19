#include "module/common.h"

void epson_pcax_init() {
        at_init();
}

MODEL m_epson_pcax = {"[286] Epson PC AX",
                      ROM_EPSON_PCAX,
                      "epson_pcax",
                      {{"", cpus_286}, {"", NULL}, {"", NULL}},
                      MODEL_GFX_NONE | MODEL_AT,
                      256,
                      15872,
                      128,
                      epson_pcax_init,
                      NULL};
