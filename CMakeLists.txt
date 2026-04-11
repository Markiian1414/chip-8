cmake_minimum_required(VERSION 3.10)
project(chip8 C)

set(CMAKE_C_STANDARD 11)

# всі .c файли
file(GLOB SOURCES "src/*.c")

# де шукати .h файли
include_directories(include)

# створюємо програму
add_executable(chip8 ${SOURCES})


find_package(SDL2 REQUIRED)
target_link_libraries(chip8 PRIVATE SDL2)