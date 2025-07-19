#include "module/common.h"
MODEL m_bull_micral_45 = {"[286] Bull Micral 45",
                          ROM_BULL_MICRAL_45,
                          "bull_micral_45",
                          {{"", cpus_286}, {"", NULL}, {"", NULL}},
                          MODEL_GFX_NONE | MODEL_AT | MODEL_HAS_IDE,
                          1024,
                          6144,
                          128,
                          ibm_at_init,
                          NULL};
