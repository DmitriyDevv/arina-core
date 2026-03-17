cmake_minimum_required(VERSION 3.28)
project(arina_core C)

set(CMAKE_C_STANDARD 11)
include_directories(include)

add_executable(arina_core
        src/main.c
        src/state.c
        src/tasks.c)
