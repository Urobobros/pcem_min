#include "module/common.h"

void ibmpcjr_init_model() {
        pcjr_init();
}

MODEL m_ibmpcjr = {"[8088] IBM PCjr", ROM_IBMPCJR, "ibmpcjr", {{"", cpus_pcjr}, {"", NULL}, {"", NULL}},
                   MODEL_GFX_FIXED,   128,         640,       64,
                   ibmpcjr_init_model,         &pcjr_device};
