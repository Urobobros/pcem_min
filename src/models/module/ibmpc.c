#include "module/common.h"
MODEL m_ibmpc = {"[8088] IBM PC", ROM_IBMPC, "ibmpc", {{"", cpus_8088}, {"", NULL}, {"", NULL}}, MODEL_GFX_NONE, 64, 640, 32,
                 xt_init,         NULL};
