#include "module/common.h"

void super16te_init() {
        xt_init();
}

MODEL m_super16te = {"[8088] Hyundai Super16TE",
                      ROM_HYUNDAI_SUPER16TE,
                      "super16te",
                      {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                      MODEL_GFX_NONE,
                      640,
                      640,
                      64,
                      super16te_init,
                      NULL};
