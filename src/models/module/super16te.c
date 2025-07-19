#include "module/common.h"
MODEL m_super16te = {"[8088] Hyundai Super16TE",
                      ROM_HYUNDAI_SUPER16TE,
                      "super16te",
                      {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                      MODEL_GFX_NONE,
                      640,
                      640,
                      64,
                      xt_init,
                      NULL};
