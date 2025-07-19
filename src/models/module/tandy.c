#include "module/common.h"

void tandy_init_model() {
        tandy1k_init();
}

MODEL m_tandy = {
        "[8088] Tandy 1000", ROM_TANDY,        "tandy", {{"", cpus_8088}, {"", NULL}, {"", NULL}}, MODEL_GFX_FIXED, 128, 640, 128,
        tandy_init_model,        &tandy1000_device};
