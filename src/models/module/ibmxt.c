#include "module/common.h"

void ibmxt_init_model() {
        xt_init();
}

MODEL m_ibmxt = {"[8088] IBM XT", ROM_IBMXT, "ibmxt",
                 {{"", cpus_8088}, {"whpx", cpus_WHPX}, {"", NULL}},
                 MODEL_GFX_NONE, 64, 640, 64,
                 ibmxt_init_model,         NULL};
