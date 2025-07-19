#include "module/common.h"

void ledge_modelm_init() {
        xt_init();
}

MODEL m_ledge_modelm = {"[8088] Leading Edge Model M",
                        ROM_LEDGE_MODELM,
                        "ledge_modelm",
                        {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                        MODEL_GFX_NONE,
                        128,
                        704,
                        64,
                        ledge_modelm_init,
                        NULL};
