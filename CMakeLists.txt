cmake_minimum_required(VERSION 3.6)
project(ex3 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex3 main.c stack.c stack.h basicMath.c basicMath.h queue.c queue.h)