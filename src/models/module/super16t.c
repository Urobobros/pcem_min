#include "module/common.h"

void super16t_init() {
        xt_init();
}

MODEL m_super16t = {"[8088] Hyundai Super16T",
                     ROM_HYUNDAI_SUPER16T,
                     "super16t",
                     {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                     MODEL_GFX_NONE,
                     640,
                     640,
                     64,
                     super16t_init,
                     NULL};
