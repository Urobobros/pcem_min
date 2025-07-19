#include "module/common.h"
MODEL m_genxt = {"[8088] Generic XT clone",
                 ROM_GENXT,
                 "genxt",
                 {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                 MODEL_GFX_NONE,
                 32,
                 704,
                 16,
                 xt_init,
                 NULL};
