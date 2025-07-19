#include "module/common.h"

void deskpro_init() {
        compaq_xt_init();
}

MODEL m_deskpro = {"[8086] Compaq Deskpro", ROM_DESKPRO, "deskpro", {{"", cpus_8086}, {"", NULL}, {"", NULL}},
                   MODEL_GFX_NONE,          128,         640,       128,
                   deskpro_init,          NULL};
