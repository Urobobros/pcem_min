#include "module/common.h"
MODEL m_dtk = {"[8088] DTK XT clone",
               ROM_DTKXT,
               "dtk",
               {{"", cpus_8088}, {"", NULL}, {"", NULL}},
               MODEL_GFX_NONE,
               64,
               640,
               64,
               xt_init,
               NULL};
