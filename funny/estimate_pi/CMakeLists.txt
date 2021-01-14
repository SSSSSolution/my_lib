cmake_minimum_required(VERSION 3.5)
project(estimate_pi)

include_directories(PUBLIC include)

add_executable(estimate_pi
    src/main.cpp
)

target_link_libraries(estimate_pi
    pthread
)

