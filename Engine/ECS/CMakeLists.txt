cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)

add_library(ECS
    STATIC
    Component.cpp
    System.cpp
    ECSManager.cpp
    SystemGroup.cpp
)