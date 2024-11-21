cmake_minimum_required(VERSION 3.28)
project(fundamental_alg C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER "/usr/bin/gcc")

set(CMAKE_C_FLAGS_DEBUG "-g")

add_executable(task2 main.c options.c)
target_link_libraries(task2 m)
