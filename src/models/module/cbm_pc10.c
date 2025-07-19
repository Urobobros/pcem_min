#include "module/common.h"
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
