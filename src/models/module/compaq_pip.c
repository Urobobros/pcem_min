#include "module/common.h"
MODEL m_compaq_pip = {"[8088] Compaq Portable Plus",
                      ROM_COMPAQ_PIP,
                      "compaq_pip",
                      {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                      MODEL_GFX_NONE,
                      128,
                      640,
                      64,
                      compaq_xt_init,
                      NULL};
