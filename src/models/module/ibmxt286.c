#include "module/common.h"
MODEL m_ibmxt286 = {"[286] IBM XT Model 286",
                    ROM_IBMXT286,
                    "ibmxt286",
                    {{"", cpus_ibmxt286}, {"", NULL}, {"", NULL}},
                    MODEL_GFX_NONE | MODEL_AT,
                    256,
                    15872,
                    128,
                    ibm_at_init,
                    NULL};

