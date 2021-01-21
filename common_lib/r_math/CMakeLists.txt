cmake_minimum_required(VERSION 3.5)
project(r_math)


add_library(r_math
    src/vec2.cpp
    include/r_math/vec2.h
    src/vec3.cpp
    include/r_math/vec3.h
    src/rect.cpp
    include/r_math/rect.h
)
target_include_directories(r_math PUBLIC include)



