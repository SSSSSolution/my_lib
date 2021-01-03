cmake_minimum_required(VERSION 3.5)
project(study_opencv)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(PUBLIC include)

add_executable(display_image
    src/display_image.cpp
)
target_link_libraries(display_image ${OpenCV_LIBS} )

