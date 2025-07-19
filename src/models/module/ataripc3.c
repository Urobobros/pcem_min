#include "module/common.h"
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
