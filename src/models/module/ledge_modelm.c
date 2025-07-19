#include "module/common.h"
MODEL m_ledge_modelm = {"[8088] Leading Edge Model M",
                        ROM_LEDGE_MODELM,
                        "ledge_modelm",
                        {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                        MODEL_GFX_NONE,
                        128,
                        704,
                        64,
                        xt_init,
                        NULL};
