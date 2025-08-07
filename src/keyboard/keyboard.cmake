set(PCEM_PRIVATE_API ${PCEM_PRIVATE_API}
        ${CMAKE_SOURCE_DIR}/includes/private/keyboard/keyboard.h
        ${CMAKE_SOURCE_DIR}/includes/private/keyboard/keyboard_xt.h
        )

set(PCEM_SRC ${PCEM_SRC}
        keyboard/keyboard.c
        keyboard/keyboard_xt.c
        )