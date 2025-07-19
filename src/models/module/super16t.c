#include "module/common.h"
MODEL m_super16t = {"[8088] Hyundai Super16T",
                     ROM_HYUNDAI_SUPER16T,
                     "super16t",
                     {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                     MODEL_GFX_NONE,
                     640,
                     640,
                     64,
                     xt_init,
                     NULL};
