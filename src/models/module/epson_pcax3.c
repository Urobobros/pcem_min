#include "module/common.h"
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
