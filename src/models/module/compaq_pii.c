#include "module/common.h"
MODEL m_compaq_pii = {"[286] Compaq Portable II",
                      ROM_COMPAQ_PII,
                      "compaq_pii",
                      {{"", cpus_286}, {"", NULL}, {"", NULL}},
                      MODEL_GFX_NONE | MODEL_AT | MODEL_HAS_IDE,
                      256,
                      15872,
                      128,
                      ibm_at_init,
                      NULL};
