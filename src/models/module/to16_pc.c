#include "module/common.h"
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

