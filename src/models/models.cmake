set(PCEM_PRIVATE_API ${PCEM_PRIVATE_API}
        ${CMAKE_SOURCE_DIR}/includes/private/models/dma.h
        ${CMAKE_SOURCE_DIR}/includes/private/models/model.h
        ${CMAKE_SOURCE_DIR}/includes/private/models/nmi.h
        ${CMAKE_SOURCE_DIR}/includes/private/models/pic.h
        ${CMAKE_SOURCE_DIR}/includes/private/models/pit.h
        ${CMAKE_SOURCE_DIR}/includes/private/models/serial.h
        )

set(PCEM_SRC ${PCEM_SRC}
        models/dma.c
        models/model.c
        models/nmi.c
        models/pic.c
        models/pit.c
        models/serial.c
        models/module/amixt.c
        )