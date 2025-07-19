#include "module/common.h"

void ataripc3_init() {
        xt_init();
}

MODEL m_ataripc3 = {"[8088] Atari PC3",
                    ROM_ATARIPC3,
                    "ataripc3",
                    {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                    MODEL_GFX_NONE,
                    64,
                    640,
                    64,
                    ataripc3_init,
                    NULL};
