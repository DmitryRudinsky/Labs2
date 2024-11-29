cmake_minimum_required(VERSION 3.28)
project(fundamental_alg CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Werror -Wextra -pedantic -Wconversion")

add_executable(task3 main.cpp)
target_link_libraries(task3 m)
