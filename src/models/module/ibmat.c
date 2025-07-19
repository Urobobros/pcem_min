#include "module/common.h"

void ibmat_init() {
        ibm_at_init();
}

MODEL m_ibmat = {"[286] IBM AT",
                 ROM_IBMAT,
                 "ibmat",
                 {{"", cpus_ibmat}, {"", NULL}, {"", NULL}},
                 MODEL_GFX_NONE | MODEL_AT,
                 256,
                 15872,
                 128,
                 ibmat_init,
                 NULL};
