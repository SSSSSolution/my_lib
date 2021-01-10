cmake_minimum_required(VERSION 3.5)
project(study_linux_ipc)

include_directories(PUBLIC include)

add_executable(posix_msg_queue
    src/main.cpp
)
target_link_libraries(posix_msg_queue
    -lrt
)

