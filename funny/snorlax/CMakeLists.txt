cmake_minimum_required(VERSION 3.5)
project(snorlax)

include_directories(PUBLIC include)
include_directories(include/snorlax)

add_executable(snorlax
    src/main.cpp
    src/frame.cpp
    src/model.cpp
    src/renderer.cpp
    src/math.cpp
    include/snorlax/math.h
    include/snorlax/frame.h
    include/snorlax/model.h
    include/snorlax/renderer.h
)

target_link_libraries(snorlax
    curses
)

