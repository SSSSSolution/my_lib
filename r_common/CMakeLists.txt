cmake_minimum_required(VERSION 3.5)
project(r_common)



include_directories(PUBLIC include)

add_library(r_common
    src/dir.cpp
    src/r_time.cpp
    src/file.cpp
    include/file.h
    src/byte_buffer.cpp
    include/byte_buffer.h
)
target_include_directories(r_common PUBLIC include)

add_executable(r_time_test
    src/r_time_test.cpp
    src/r_time.cpp
)
target_include_directories(r_time_test PUBLIC src)


find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(dir_test
    src/dir.cpp
    test/dir_test/main.cpp
)
target_link_libraries(dir_test ${GTEST_BOTH_LIBRARIES})
target_link_libraries(dir_test ${CMAKE_THREAD_LIBS_INIT})

add_executable(file_test
    src/file.cpp
    test/file_test/main.cpp
)
#target_link_libraries(file_test ${GTEST_BOTH_LIBRARIES})
#target_link_libraries(file_test ${CMAKE_THREAD_LIBS_INIT})

add_test(Test dir_test)
enable_testing()


