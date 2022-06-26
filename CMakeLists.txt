cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
# SET(CMAKE_CXX_FLAGS  "-Wall" "-Wpedantic" "-Werror" "-Wextra")

project(Particles VERSION 1.0)


include_directories(${PROJECT_SOURCE_DIR})

file(GLOB particles_SRC "*.cpp")
add_executable(Particles ${particles_SRC})
target_compile_options(Particles PRIVATE "-Wall" "-Wpedantic" "-Werror" "-Wextra")

set_target_properties(Particles PROPERTIES CXX_STANDARD 17)

target_link_libraries(Particles -lsfml-graphics -lsfml-window -lsfml-system)
