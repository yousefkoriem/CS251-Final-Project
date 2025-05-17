cmake_minimum_required(VERSION 3.31)
project(Graphics)

set(CMAKE_CXX_STANDARD 20)

add_executable(Graphics main.cpp)
find_package(OpenGL REQUIRED)

# Replace this path with your actual FreeGLUT installation path if needed
include_directories("C:/msys64/ucrt64/include")
link_directories("C:/msys64/ucrt64/lib")

target_link_libraries(Graphics
        OpenGL::GL
        freeglut
        glu32
        opengl32
        winmm
        gdi32
)