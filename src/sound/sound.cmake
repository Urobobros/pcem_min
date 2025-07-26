set(PCEM_PRIVATE_API ${PCEM_PRIVATE_API}
        ${CMAKE_SOURCE_DIR}/includes/private/sound/ayumi/ayumi.h
        ${CMAKE_SOURCE_DIR}/includes/private/sound/resid-fp/envelope.h
        ${CMAKE_SOURCE_DIR}/includes/private/sound/resid-fp/extfilt.h
        ${CMAKE_SOURCE_DIR}/includes/private/sound/resid-fp/filter.h
        ${CMAKE_SOURCE_DIR}/includes/private/sound/resid-fp/pot.h
        ${CMAKE_SOURCE_DIR}/includes/private/sound/resid-fp/siddefs-fp.h
        ${CMAKE_SOURCE_DIR}/includes/private/sound/resid-fp/sid.h
        ${CMAKE_SOURCE_DIR}/includes/private/sound/resid-fp/voice.h
        ${CMAKE_SOURCE_DIR}/includes/private/sound/resid-fp/wave.h
        ${CMAKE_SOURCE_DIR}/includes/private/sound/sound.h
        ${CMAKE_SOURCE_DIR}/includes/private/sound/sound_speaker.h
        )

set(PCEM_SRC ${PCEM_SRC}
        sound/sound.c
        sound/sound_speaker.c
        sound/soundopenal.c
        )

# AYUMI
set(PCEM_SRC ${PCEM_SRC}
        sound/ayumi/ayumi.c
        )

# RESID-FP
set(PCEM_SRC ${PCEM_SRC}
        sound/resid-fp/convolve.cc
        sound/resid-fp/convolve-sse.cc
        sound/resid-fp/envelope.cc
        sound/resid-fp/extfilt.cc
        sound/resid-fp/filter.cc
        sound/resid-fp/pot.cc
        sound/resid-fp/sid.cc
        sound/resid-fp/voice.cc
        sound/resid-fp/wave6581_PS_.cc
        sound/resid-fp/wave6581_PST.cc
        sound/resid-fp/wave6581_P_T.cc
        sound/resid-fp/wave6581__ST.cc
        sound/resid-fp/wave8580_PS_.cc
        sound/resid-fp/wave8580_PST.cc
        sound/resid-fp/wave8580_P_T.cc
        sound/resid-fp/wave8580__ST.cc
        sound/resid-fp/wave.cc
        )

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux" AND USE_ALSA)
        set(PCEM_ADDITIONAL_LIBS ${PCEM_ADDITIONAL_LIBS} ${ALSA_LIBRARIES})
endif()
