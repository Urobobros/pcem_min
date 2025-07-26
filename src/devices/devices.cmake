set(PCEM_PRIVATE_API ${PCEM_PRIVATE_API}
        ${CMAKE_SOURCE_DIR}/includes/private/devices/nvr.h
        ${CMAKE_SOURCE_DIR}/includes/private/devices/ps2_nvr.h
        )

set(PCEM_SRC ${PCEM_SRC}
        devices/nvr.c
        devices/ps2_nvr.c
        )