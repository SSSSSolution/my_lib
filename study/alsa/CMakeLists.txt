cmake_minimum_required(VERSION 3.5)
project(study_alsa)

find_package(ALSA REQUIRED)

include_directories(PUBLIC include)
include_directories(PRIVATE ${ALSA_INCLUDE_DIRS})

add_executable(study_alsa
    src/main.cpp
)
target_link_libraries(study_alsa
    r_log
    ${ALSA_LIBRARIES}
)

install(TARGETS
    study_alsa
    DESTINATION bin/
)

