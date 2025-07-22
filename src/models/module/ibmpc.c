#include "module/common.h"

void ibmpc_init() {
        xt_init();
}

MODEL m_ibmpc = {"[8088] IBM PC", ROM_IBMPC, "ibmpc",
                 {{"", cpus_8088}, {"whpx", cpus_WHPX}, {"", NULL}},
                 MODEL_GFX_NONE, 64, 640, 32,
                 ibmpc_init,         NULL};
