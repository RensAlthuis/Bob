cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)
project(Engine VERSION 0.1.0)
add_executable(engine main.cpp)

add_subdirectory(Engine)

include_directories(
    Engine/Libraries/include
)
target_link_libraries(engine Engine)