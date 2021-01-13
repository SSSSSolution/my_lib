cmake_minimum_required(VERSION 3.10)
project(r_render_system)

set(CMAKE_VERBOSE_MAKEFILEON ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

find_package(Vulkan REQUIRED FATAL_ERROR)
include_directories(${Vulkan_INCLUDE_DIR})
include_directories(include/render_system)
include_directories(src/shader)
include_directories(src/vulkan_renderer)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/data)

find_package(PythonInterp 3 REQUIRED)
find_program(GLSLANG_VALIDATOR NAMES glslangValidator
              HINTS ${VULKAN_SKD}/bin)
message(STATUS "GLSLANG_VALIDATOR = " ${GLSLANG_VALIDATOR})

message(STATUS "CMAKE_SOURCE_DIR = " ${CMAKE_SOURCE_DIR})
macro(glsl_to_spirv src)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${src}.h
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/scripts/generate_spirv.py ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/${src} ${CMAKE_CURRENT_BINARY_DIR}/${src}.h ${GLSLANG_VALIDATOR} false
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/scripts/generate_spirv.py ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/${src} ${GLSLANG_VALIDATOR}
        )
endmacro()


message(STATUS "CMAKE_CURRENT_BINARY_DIR = " ${CMAKE_CURRENT_BINARY_DIR})
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/draw_cube.vert)
    message(STATUS "glsl_to_spirv(init_shader.vert)")
    glsl_to_spirv(draw_cube.vert)
    set(sources ${sources} draw_cube.vert.h )
endif()
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/draw_cube.frag)
    message(STATUS "glsl_to_spirv(init_shader.frag)")
    glsl_to_spirv(draw_cube.frag)
    set(sources ${sources} draw_cube.frag.h)
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/triangle.vert)
    message(STATUS "glsl_to_spirv(init_shader.vert)")
    glsl_to_spirv(triangle.vert)
    set(sources ${sources} triangle.vert.h )
endif()
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/shader/triangle.frag)
    message(STATUS "glsl_to_spirv(init_shader.frag)")
    glsl_to_spirv(triangle.frag)
    set(sources ${sources} triangle.frag.h)
endif()

message(STATUS "sources = " ${sources})
add_executable(r_render_system
    ${sources}
    src/main.cpp
    src/r_window.h
    src/xlib_window/r_window.cpp
    src/r_renderer.h
    src/vulkan_renderer/r_renderer.cpp
    src/window_info.h
    src/camera.cpp
    src/vulkan_renderer/vulkan_context.h
    src/vulkan_renderer/vulkan_context.cpp
    src/vulkan_renderer/instance_initializer.h
    src/vulkan_renderer/instance_initializer.cpp
    src/vulkan_renderer/physical_device_initializer.h
    src/vulkan_renderer/physical_device_initializer.cpp
    src/vulkan_renderer/surface_initializer.h
    src/vulkan_renderer/surface_initializer.cpp
    src/vulkan_renderer/device_initializer.h
    src/vulkan_renderer/device_initializer.cpp
    src/vulkan_renderer/swapchain_initializer.h
    src/vulkan_renderer/swapchain_initializer.cpp
    src/vulkan_renderer/command_pool_initializer.h
    src/vulkan_renderer/command_pool_initializer.cpp
    src/vulkan_renderer/command_buffer_initializer.h
    src/vulkan_renderer/command_buffer_initializer.cpp
    src/vulkan_renderer/vulkan_helper.h
    src/vulkan_renderer/vulkan_helper.cpp
    src/vulkan_renderer/depth_buffer_initializer.h
    src/vulkan_renderer/depth_buffer_initializer.cpp
#    src/vulkan_renderer/uniform_buffer_initializer.h
#    src/vulkan_renderer/uniform_buffer_initializer.cpp
#    src/vulkan_renderer/descriptor_and_pipeline_initializer.h
#    src/vulkan_renderer/descriptor_and_pipeline_initializer.cpp
    src/vulkan_renderer/renderpass_initializer.h
    src/vulkan_renderer/renderpass_initializer.cpp
    src/vulkan_renderer/shader_initializer.h
    src/vulkan_renderer/shader_initializer.cpp
    src/vulkan_renderer/framebuffer_initializer.h
    src/vulkan_renderer/framebuffer_initializer.cpp
    src/vulkan_renderer/vertex_buffer_initializer.h
    src/vulkan_renderer/vertex_buffer_initializer.cpp
    src/vulkan_renderer/descriptor_pool_initializer.h
    src/vulkan_renderer/descriptor_pool_initializer.cpp
    src/vulkan_renderer/descriptor_set_initializer.h
    src/vulkan_renderer/descriptor_set_initializer.cpp
    src/vulkan_renderer/pipeline_initializer.h
    src/vulkan_renderer/pipeline_initializer.cpp
    src/vulkan_renderer/descriptor_set_layout_initializer.h
    src/vulkan_renderer/descriptor_set_layout_initializer.cpp
    src/vulkan_renderer/texture_initializer.h
    src/vulkan_renderer/texture_initializer.cpp
    src/resources/texture.cpp
    src/resources/texture.h

)

target_include_directories(r_render_system PRIVATE src)

target_link_libraries(r_render_system
    r_log
    X11
    ${Vulkan_LIBRARIES}
    pthread
)
