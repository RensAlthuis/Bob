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
Texture.cpp
)


include_directories(
    ${PROJECT_SOURCE_DIR}/Libraries/include
)

find_library(
    GLFW glfw3
    HINTS "Libraries/lib/"
)
find_library(
    FREEIMAGE freeimage
    HINTS "Libraries/lib/"
)
set(COMMONLIBS Maths ${FREEIMAGE} ${GLFW})

target_link_libraries(Engine 
    ${COMMONLIBS}
    GL 
    dl 
    pthread 
    X11 
    Xi 
    Xrandr 
    Xxf86vm 
    Xinerama 
    Xcursor
)