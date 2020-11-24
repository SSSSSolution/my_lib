cmake_minimum_required(VERSION 3.5)
project(r_common)

add_executable(r_time_test
    src/r_time_test.cpp
    src/r_time.cpp
)

target_include_directories(r_time_test PUBLIC src)
