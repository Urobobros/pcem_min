#include "module/common.h"

void tandy1000hx_init() {
        tandy1k_init();
}

MODEL m_tandy1000hx = {"[8088] Tandy 1000 HX",
                       ROM_TANDY1000HX,
                       "tandy1000hx",
                       {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                       MODEL_GFX_FIXED,
                       256,
                       640,
                       128,
                       tandy1000hx_init,
                       &tandy1000hx_device};
