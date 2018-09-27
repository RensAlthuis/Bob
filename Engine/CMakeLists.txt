cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)

subdirs(Maths)

add_library(Engine
STATIC
ElementBuffer.cpp
FileReader.h
glad.c
Input.cpp
Shader.cpp
VertexArray.cpp
VertexBuffer.cpp
Window.cpp
)


include_directories(
    ${PROJECT_SOURCE_DIR}/Libraries/include
)

target_link_libraries(Engine 
    Maths 
    GL 
    glfw3 
    dl 
    pthread 
    X11 
    Xi 
    Xrandr 
    Xxf86vm 
    Xinerama 
    Xcursor
)