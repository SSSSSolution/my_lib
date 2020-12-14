cmake_minimum_required(VERSION 3.5)

project(panda)

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

add_executable(panda
  src/main.cpp
  src/cmd/panda_cmd.cpp
  src/cmd/plan_cmd.cpp
  src/plan_handle.cpp
)

target_link_libraries(panda
    r_log
    command_processor
)

install(TARGETS
    panda
    DESTINATION bin/${PROJECT_NAME}
)
