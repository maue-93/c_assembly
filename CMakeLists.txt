cmake_minimum_required(VERSION 3.26)
project(cs203lab5 C)

set(CMAKE_C_STANDARD 11)

add_executable(cs203lab5 main.c
        cpu.h
        cpu.c
        mem.h
        mem.c
        helper_methods.h
        helper_methods.c
)

add_executable(test_helper_methods test_helper_methods.c helper_methods.c)

add_executable(test_cpu test_cpu.c cpu.c helper_methods.c mem.c)

add_executable(test_mem test_mem.c mem.c cpu.c helper_methods.c)
