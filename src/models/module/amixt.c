#include "module/common.h"

void amixt_init() {
        xt_init();
}

MODEL m_amixt = {"[8088] AMI XT clone",
                 ROM_AMIXT,
                 "amixt",
                 {{"", cpus_8088}, {"", NULL}, {"", NULL}},
                 MODEL_GFX_NONE,
                 64,
                 640,
                 64,
                 amixt_init,
                 NULL};
