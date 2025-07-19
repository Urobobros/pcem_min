#include "module/common.h"

void ibmxt286_init() {
        ibm_at_init();
}

MODEL m_ibmxt286 = {"[286] IBM XT Model 286",
                    ROM_IBMXT286,
                    "ibmxt286",
                    {{"", cpus_ibmxt286}, {"", NULL}, {"", NULL}},
                    MODEL_GFX_NONE | MODEL_AT,
                    256,
                    15872,
                    128,
                    ibmxt286_init,
                    NULL};

