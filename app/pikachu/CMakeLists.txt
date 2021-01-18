cmake_minimum_required(VERSION 3.5)

project(pikachu)

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

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include/${PROJECT_NAME})

set(CMAKE_AUTOMOC ON)

#qt5_wrap_cpp( MOC widget.h)

add_executable(pikachu
  src/main.cpp
  src/pikachu_app.cpp
  src/preloading_widget.cpp
  src/main_window.cpp
  src/picture_widget.cpp
  src/control_bar.cpp
  src/conversion_handle.cpp
  src/about_dialog.cpp
  src/config.cpp
  include/pikachu/config.h
  include/pikachu/about_dialog.h
  include/pikachu/conversion_handle.h
  include/pikachu/main_window.h
  include/pikachu/pikachu_app.h
  include/pikachu/preloading_widget.h
  include/pikachu/picture_widget.h
  include/pikachu/control_bar.h
)

target_link_libraries(pikachu
    r_log
    command_processor
    r_common
    Qt5::Widgets
    pthread
    ${OpenCV_LIBS}
)

install(TARGETS
    pikachu
    DESTINATION bin/
)
