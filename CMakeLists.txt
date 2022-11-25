cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)

project(Particles VERSION 1.0)

include_directories(${PROJECT_SOURCE_DIR})
include_directories("/usr/include/c++/9/optional")

file(GLOB particles_SRC "*.cpp")
add_executable(Particles ${particles_SRC})
target_compile_options(Particles PRIVATE "-g" "-Og" "-Wall" "-Wpedantic" "-Werror" "-Wextra")

set_target_properties(Particles PROPERTIES CXX_STANDARD 17)

target_link_libraries(Particles -lpthread -lsfml-graphics -lsfml-window -lsfml-system -lX11)
