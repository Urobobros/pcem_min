set(PCEM_PRIVATE_API ${PCEM_PRIVATE_API}
        ${CMAKE_SOURCE_DIR}/includes/private/mouse/mouse.h
        ${CMAKE_SOURCE_DIR}/includes/private/mouse/mouse_serial.h
        )

set(PCEM_SRC ${PCEM_SRC}
        mouse/mouse.c
        mouse/mouse_serial.c
        )