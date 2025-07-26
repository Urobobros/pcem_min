set(PCEM_PRIVATE_API ${PCEM_PRIVATE_API}
        ${CMAKE_SOURCE_DIR}/includes/private/ide/ide_atapi.h
        ${CMAKE_SOURCE_DIR}/includes/private/ide/ide.h
        )

set(PCEM_SRC ${PCEM_SRC}
        ide/ide.c
        ide/ide_atapi.c
        )