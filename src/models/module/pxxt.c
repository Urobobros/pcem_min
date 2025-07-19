#include "module/common.h"

void pxxt_init() {
        xt_init();
}

MODEL m_pxxt = {"[8088] Phoenix XT clone",
                ROM_PXXT,
                "pxxt",
                {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                MODEL_GFX_NONE,
                64,
                640,
                64,
                pxxt_init,
                NULL};
