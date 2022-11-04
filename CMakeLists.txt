cmake_minimum_required(VERSION 3.23)
project(graphicsTest C)

set(CMAKE_C_STANDARD 99)

add_executable(graphicsTest main.c tigr.h tigr.c physics.h physics.c graphics.h graphics.c geometry.c geometry.h controls.h controls.c)

target_link_libraries(graphicsTest "-lm")
target_link_libraries(graphicsTest "-lGLU")
target_link_libraries(graphicsTest "-lGL")
target_link_libraries(graphicsTest "-lX11")
