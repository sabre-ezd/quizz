cmake_minimum_required(VERSION 3.15)
project(quizz)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
add_executable(quizz main.cpp struct.h)