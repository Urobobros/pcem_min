#include "module/common.h"
MODEL m_tulip_tc7 = {"[286] Tulip AT Compact",
                     ROM_TULIP_TC7,
                     "tulip_tc7",
                     {{"", cpus_286}, {"", NULL}, {"", NULL}},
                     MODEL_GFX_NONE | MODEL_AT | MODEL_HAS_IDE,
                     640,
                     15872,
                     128,
                     ibm_at_init,
                     NULL};



