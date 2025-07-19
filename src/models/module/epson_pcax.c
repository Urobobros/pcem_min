#include "module/common.h"
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
