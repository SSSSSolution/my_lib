cmake_minimum_required(VERSION 3.5)
project(r_render_system)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

add_executable(r_render_system
    src/main.cpp
    src/r_window.h
    src/xlib_window/r_window.cpp
    src/r_renderer.h
    src/vulkan_renderer/r_renderer.cpp
)

target_include_directories(r_render_system PRIVATE src)

target_link_libraries(r_render_system
    r_log
    X11
)
