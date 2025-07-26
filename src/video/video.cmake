set(PCEM_PRIVATE_API ${PCEM_PRIVATE_API}
        ${CMAKE_SOURCE_DIR}/includes/private/video/video.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_sdac_ramdac.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_stg_ramdac.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_svga.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_svga_render.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_svga_render_remap.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_cga.h
        )

if(USE_EXPERIMENTAL AND USE_EXPERIMENTAL_PGC)
        set(PCEM_DEFINES ${PCEM_DEFINES} USE_EXPERIMENTAL_PGC)
endif()

set(PCEM_SRC ${PCEM_SRC}
        video/vid_cga.c
        video/vid_sdac_ramdac.c
        video/vid_stg_ramdac.c
        video/vid_svga.c
        video/vid_svga_render.c
        video/video.c
        )
