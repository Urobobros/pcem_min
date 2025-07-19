#include "module/common.h"
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


