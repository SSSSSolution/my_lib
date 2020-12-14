cmake_minimum_required(VERSION 3.5)
set(CMAKE_INSTALL_PREFIX /)
project(r_lib)

include_directories(PUBLIC nlohmann)

add_subdirectory(r_log)
add_subdirectory(r_common)
add_subdirectory(r_render_system)
add_subdirectory(r_argument_processor)


add_subdirectory(app/panda)

