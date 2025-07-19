#include "module/common.h"
MODEL m_ibmpcjr = {"[8088] IBM PCjr", ROM_IBMPCJR, "ibmpcjr", {{"", cpus_pcjr}, {"", NULL}, {"", NULL}},
                   MODEL_GFX_FIXED,   128,         640,       64,
                   pcjr_init,         &pcjr_device};
