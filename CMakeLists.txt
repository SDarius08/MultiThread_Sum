cmake_minimum_required(VERSION 3.28)
project(MultiThread_Sum C)

set(CMAKE_C_STANDARD 11)

add_executable(MultiThread_Sum main.c
        headers/functions.h
        functions/functions.c
        headers/file_handling.h
        functions/file_handling.c
        headers/error_handling.h
        functions/error_handling.c
        headers/lumb_list.h
        functions/lumb_list.c)
