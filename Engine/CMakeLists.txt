cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)

if(WIN32)
    set(OS Windows)
else()
    set(OS Linux)
endif()

add_subdirectory(Maths)
add_subdirectory(ECS)

add_library(Engine STATIC
glad.c
Window.cpp
FileReader.h
Input.cpp
Shader.cpp
Time.cpp
Texture.cpp
Model.cpp
Camera.cpp
Object.cpp
ModelRenderer.cpp
DirectionalLight.cpp
PointLight.cpp
SpotLight.cpp
Buffer/ElementBuffer.cpp
Buffer/VertexArray.cpp
Buffer/VertexBuffer.cpp
Buffer/FrameBuffer.cpp
Transform.cpp
RenderSystem.cpp
)

include_directories(
    Libraries/include
)

find_library(
    GLFW glfw3
    HINTS Libraries/lib/${OS}
)
find_library(
    FREEIMAGE freeimage
    HINTS Libraries/lib/${OS}
)

message(STATUS "Found Library" ${GLFW})
message(STATUS "Found Library" ${FREEIMAGE})

set(COMMONLIBS Maths ECS ${FREEIMAGE} ${GLFW})

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