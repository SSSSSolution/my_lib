cmake_minimum_required(VERSION 3.5)
project(r_math)


add_library(r_math
    src/vec2.cpp
    include/r_math/vec2.h
    src/vec3.cpp
    include/r_math/vec3.h
    src/vec4.cpp
    include/r_math/vec4.h
    src/rect.cpp
    include/r_math/rect.h
    src/mat4.cpp
    include/r_math/mat4.h
)
target_include_directories(r_math PUBLIC include)

add_executable(r_math_test
    test/r_math_test.cpp
)
target_link_libraries(r_math_test r_math)



