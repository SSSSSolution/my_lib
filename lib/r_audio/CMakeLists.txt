cmake_minimum_required(VERSION 3.5)
project(r_audio)

find_package(ALSA REQUIRED)

include_directories(PUBLIC include)
include_directories(PRIVATE ${ALSA_INCLUDE_DIRS})

add_library(r_audio
    include/r_audio/wav.h
    src/wav.cpp
    include/r_audio/wav_player.h
    src/wav_player.cpp
)
target_link_libraries(r_audio
    r_log
    ${ALSA_LIBRARIES}
)


add_executable(r_audio_test
    tool/r_audio_test.cpp
)
target_link_libraries(r_audio_test
    r_log
    r_audio
#    ${ALSA_LIBRARIES}
)

install(TARGETS
    r_audio_test
    DESTINATION bin/
)

