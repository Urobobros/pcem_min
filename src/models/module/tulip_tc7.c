#include "module/common.h"

void tulip_tc7_init() {
        ibm_at_init();
}

MODEL m_tulip_tc7 = {"[286] Tulip AT Compact",
                     ROM_TULIP_TC7,
                     "tulip_tc7",
                     {{"", cpus_286}, {"", NULL}, {"", NULL}},
                     MODEL_GFX_NONE | MODEL_AT | MODEL_HAS_IDE,
                     640,
                     15872,
                     128,
                     tulip_tc7_init,
                     NULL};



