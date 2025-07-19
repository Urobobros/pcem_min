#include "module/common.h"
MODEL m_jukopc = {"[8088] Juko XT clone",
                  ROM_JUKOPC,
                  "jukopc",
                  {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                  MODEL_GFX_NONE,
                  64,
                  640,
                  64,
                  xt_init,
                  NULL};
