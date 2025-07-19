#include "module/common.h"

void dtk_init() {
        xt_init();
}

MODEL m_dtk = {"[8088] DTK XT clone",
               ROM_DTKXT,
               "dtk",
               {{"", cpus_8088}, {"", NULL}, {"", NULL}},
               MODEL_GFX_NONE,
               64,
               640,
               64,
               dtk_init,
               NULL};
