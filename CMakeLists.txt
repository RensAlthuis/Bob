cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
project(Squash VERSION 0.1.0)
add_executable(Squash main.cpp)

add_subdirectory(Engine)

include_directories(
    Engine/Libraries/include
)
target_link_libraries(Squash Engine)