cmake_minimum_required(VERSION 3.5)
set(CMAKE_INSTALL_PREFIX /)
project(r_lib)

include_directories(PUBLIC nlohmann)
include_directories(PUBLIC glm)
include_directories(PUBLIC fbx/include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(r_log)
add_subdirectory(r_common)
add_subdirectory(r_render_system)
add_subdirectory(r_argument_processor)


add_subdirectory(app/panda)

add_subdirectory(study/ipc/linux)
add_subdirectory(study/fbx)

enable_testing()
