#include "module/common.h"
MODEL m_ncr_pc4i = {"[8088] NCR PC4i", ROM_NCR_PC4I, "ncr_pc4i", {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                    MODEL_GFX_NONE,    256,          640,        64,
                    xt_init,           NULL};
