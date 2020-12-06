cmake_minimum_required(VERSION 3.5)
project(r_log)

add_executable(rlog_test
    src/main.cpp
    src/rlog.cpp
)
target_include_directories(rlog_test PUBLIC src)

add_library(r_log
    src/rlog.cpp
)
target_include_directories(r_log PUBLIC src)


