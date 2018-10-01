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
Model.cpp
Camera.cpp
Object.cpp
)


include_directories(
    ${PROJECT_SOURCE_DIR}/Libraries/include
)

find_library(
    GLFW glfw3
    HINTS Libraries/lib/${OS}
)
find_library(
    FREEIMAGE freeimage
    HINTS Libraries/lib/${OS}
)

message("Found Library" ${GLFW})
message("Found Library" ${FREEIMAGE})

set(COMMONLIBS Maths ${FREEIMAGE} ${GLFW})

if(WIN32)
    target_link_libraries(Engine
    ${COMMONLIBS}
    ws2_32
    )
else()
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
endif()