cmake_minimum_required(VERSION 3.28)
project(fundamental_alg C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER "/usr/bin/gcc")

set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Werror -Wextra -pedantic -Wconversion")

add_executable(task10 main.c)
target_link_libraries(task10 m)
