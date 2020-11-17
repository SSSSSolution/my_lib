cmake_minimum_required(VERSION 3.5)
project(rlog)

add_executable(rlog
    src/main.cpp
    src/rlog.cpp
)

target_include_directories(rlog PRIVATE src)
