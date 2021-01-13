cmake_minimum_required(VERSION 3.5)
project(study_fbx)

include_directories(PUBLIC include)

link_directories(${PROJECT_SOURCE_DIR}/../../fbx/lib/gcc/x64/release)
add_executable(study_fbx
    src/main.cpp
)
target_link_libraries(study_fbx
    libfbxsdk.so
    pthread
    xml2
)

