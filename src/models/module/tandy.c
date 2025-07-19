#include "module/common.h"
MODEL m_tandy = {
        "[8088] Tandy 1000", ROM_TANDY,        "tandy", {{"", cpus_8088}, {"", NULL}, {"", NULL}}, MODEL_GFX_FIXED, 128, 640, 128,
        tandy1k_init,        &tandy1000_device};
