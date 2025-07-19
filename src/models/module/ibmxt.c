#include "module/common.h"
MODEL m_ibmxt = {"[8088] IBM XT", ROM_IBMXT, "ibmxt", {{"", cpus_8088}, {"", NULL}, {"", NULL}}, MODEL_GFX_NONE, 64, 640, 64,
                 xt_init,         NULL};
