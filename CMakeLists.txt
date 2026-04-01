cmake_minimum_required(VERSION 3.10)
project(CHIP8 C)

set(CMAKE_C_STANDARD 11)

# Додаємо include/
include_directories(include)

# Додаємо всі .c файли з src
file(GLOB SOURCES "src/*.c")

# Створюємо виконуваний файл
add_executable(chip-8 ${SOURCES})