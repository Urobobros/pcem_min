set(PCEM_PRIVATE_API ${PCEM_PRIVATE_API}
        ${CMAKE_SOURCE_DIR}/includes/private/video/video.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_cga.h
        )

if(USE_EXPERIMENTAL AND USE_EXPERIMENTAL_PGC)
        set(PCEM_DEFINES ${PCEM_DEFINES} USE_EXPERIMENTAL_PGC)
endif()

set(PCEM_SRC ${PCEM_SRC}
        video/vid_cga.c
        video/video.c
        )
