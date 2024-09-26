cmake_minimum_required(VERSION 3.10)

project(OpenGLTest)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILE clang)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/lib)

add_executable(main src/main.c)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs/include)
target_link_libraries(main glew32s glfw3 opengl32)