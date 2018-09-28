cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
project(Bob VERSION 0.1.0)
add_executable(Bob main.cpp)

find_package(OpenGL REQUIRED)

subdirs(Engine)
include_directories(
    ${PROJECT_SOURCE_DIR}/Engine
    ${PROJECT_SOURCE_DIR}/Engine/Libraries/include
)

target_link_libraries(Bob Engine)