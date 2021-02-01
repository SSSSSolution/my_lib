cmake_minimum_required(VERSION 3.5)

project(charizard)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(OpenCV REQUIRED)
find_package(X11 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${X11_INCLUDE_DIRS})
include_directories(include/${PROJECT_NAME})

set(CMAKE_AUTOMOC ON)

add_executable(charizard
  src/main.cpp
  src/main_window.cpp
  include/charizard/main_window.h
  src/control_bar_widget.cpp
  include/charizard/control_bar_widget.h
  src/render_handle.cpp
  include/charizard/render_handle.h
  src/soft_renderer.cpp
  include/charizard/soft_renderer.h
  src/model.cpp
  include/charizard/model.h
  src/exector.cpp
  include/charizard/exector.h
  src/camera.cpp
  include/charizard/camera.h
  src/native_widget.cpp
  include/charizard/native_widget.h
  src/scenes.cpp
  include/charizard/scenes.h
  src/types.cpp
  include/charizard/types.h
  src/clipper.cpp
  include/charizard/clipper.h
)

target_link_libraries(charizard
    Qt5::Widgets
    pthread
    ${OpenCV_LIBS}
    r_math
    r_log
    X11
)

install(TARGETS
    charizard
    DESTINATION bin/
)
