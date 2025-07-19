#include "module/common.h"
MODEL m_sis496 = {"[486] Award SiS 496/497",
                  ROM_SIS496,
                  "sis496",
                  {{"Intel", cpus_i486}, {"AMD", cpus_Am486}, {"Cyrix", cpus_Cx486}},
                  MODEL_GFX_NONE | MODEL_AT | MODEL_PCI | MODEL_HAS_IDE,
                  1,
                  256,
                  1,
                  at_sis496_init,
                  NULL};

