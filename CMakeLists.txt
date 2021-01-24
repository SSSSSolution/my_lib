cmake_minimum_required(VERSION 3.5)
set(CMAKE_INSTALL_PREFIX /)
project(r_lib)

include_directories(PUBLIC nlohmann)
include_directories(PUBLIC glm)
include_directories(PUBLIC fbx/include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_subdirectory(r_log)
add_subdirectory(r_common)
add_subdirectory(r_render_system)
add_subdirectory(common_lib/r_math)
add_subdirectory(r_argument_processor)
add_subdirectory(study/opencv)
add_subdirectory(funny)

add_subdirectory(app/panda)
add_subdirectory(app/pikachu)
add_subdirectory(app/charizard)


add_subdirectory(study/ipc/linux)
#add_subdirectory(study/fbx)

enable_testing()
