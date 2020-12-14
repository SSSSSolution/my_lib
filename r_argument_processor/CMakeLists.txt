cmake_minimum_required(VERSION 3.5)

set(CMAKE_INSTALL_PREFIX "/")

project(command_processor)

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

include_directories(include/${PROJECT_NAME})

add_library(command_processor
    src/command_processor.cpp
)
target_include_directories(command_processor PUBLIC include/${PROJECT_NAME})

add_executable(command_processor_test
  src/main.cpp
  src/command_processor.cpp
)

install(TARGETS
    command_processor_test
    DESTINATION test/${PROJECT_NAME}
)

install(DIRECTORY
    include/
    DESTINATION include
)

install(TARGETS
    command_processor
    DESTINATION lib
)
