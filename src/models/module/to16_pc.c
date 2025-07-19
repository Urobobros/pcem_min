#include "module/common.h"

void to16_pc_init() {
        xt_init();
}

MODEL m_to16_pc = {"[8088] Thomson TO16 PC",
                   ROM_TO16_PC,
                   "to16_pc",
                   {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                   MODEL_GFX_NONE,
                   512,
                   640,
                   128,
                   to16_pc_init,
                   NULL};

