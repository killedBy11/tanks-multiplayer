cmake_minimum_required(VERSION 3.23)
project(graphicsTest C)

set(CMAKE_C_STANDARD 99)

add_executable(graphicsTest main.c graphics/tigr.h graphics/tigr.c physics/physics.h physics/physics.c graphics/graphics.h graphics/graphics.c geometry/geometry.c geometry/geometry.h controls/controls.h controls/controls.c flags.h measurement_units.h)

target_link_libraries(graphicsTest "-lm")
target_link_libraries(graphicsTest "-lGLU")
target_link_libraries(graphicsTest "-lGL")
target_link_libraries(graphicsTest "-lX11")

