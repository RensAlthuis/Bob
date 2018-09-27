cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)

add_library(Maths
    STATIC
    Matrix4.cpp
    Vector2.cpp
    Vector3.cpp
    Vector4.cpp
)