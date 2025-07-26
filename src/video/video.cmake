set(PCEM_PRIVATE_API ${PCEM_PRIVATE_API}
        ${CMAKE_SOURCE_DIR}/includes/private/video/video.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_sdac_ramdac.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_sigma.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_stg_ramdac.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_svga.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_svga_render.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_svga_render_remap.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_t1000.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_t3100e.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_tandy.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_tandysl.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_tgui9440.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_tkd8001_ramdac.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_tvga.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_tvp3026_ramdac.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_unk_ramdac.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_vga.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_wy700.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_ati_eeprom.h
        ${CMAKE_SOURCE_DIR}/includes/private/video/vid_cga.h
        )

if(USE_EXPERIMENTAL AND USE_EXPERIMENTAL_PGC)
        set(PCEM_DEFINES ${PCEM_DEFINES} USE_EXPERIMENTAL_PGC)
endif()

set(PCEM_SRC ${PCEM_SRC}
        video/vid_cga.c
        video/vid_sdac_ramdac.c
        video/vid_sigma.c
        video/vid_stg_ramdac.c
        video/vid_svga.c
        video/vid_svga_render.c
        video/vid_t1000.c
        video/vid_t3100e.c
        video/vid_tandy.c
        video/vid_tandysl.c
        video/vid_tgui9440.c
        video/vid_tkd8001_ramdac.c
        video/vid_tvga.c
        video/vid_tvp3026_ramdac.c
        video/vid_unk_ramdac.c
        video/vid_vga.c
        video/vid_wy700.c
        video/video.c
        )
