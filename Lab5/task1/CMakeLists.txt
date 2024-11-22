cmake_minimum_required(VERSION 3.28)
project(fundamental_alg CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_executable(task1 main.cpp binary.cpp)
target_link_libraries(task1 m)
