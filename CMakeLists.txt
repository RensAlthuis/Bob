cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)
project(Bob VERSION 0.1.0)
add_executable(Bob main.cpp)

include(CTest)
enable_testing()
find_package(OpenGL REQUIRED)

subdirs(Engine)
include_directories(
    ${PROJECT_SOURCE_DIR}/Engine
    ${PROJECT_SOURCE_DIR}/Engine/Libraries/include
)

add_custom_target(Assets)

FILE(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/Assets" source)
FILE(TO_NATIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}/Assets" destination)

IF (WIN32)
add_custom_command(
TARGET Assets POST_BUILD
COMMAND mklink /D ${destination} ${source}
DEPENDS ${destination}
COMMENT "symbolic link Assets folder from ${source} => ${destination}"
)
ELSE()
add_custom_command(
TARGET Assets POST_BUILD
COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
DEPENDS ${destination}
COMMENT "symbolic link Assets folder from ${source} => ${destination}"
)
ENDIF()

find_library(
    FREEIMAGE freeimage
    HINTS "Engine/Libraries/lib/"
)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
target_link_libraries(Bob Engine ${FREEIMAGE})
add_dependencies(Bob Assets)