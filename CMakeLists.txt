cmake_minimum_required(VERSION 3.27)
project(Sem2 C)

set(CMAKE_C_STANDARD 23)

add_executable(Sem2 main.c
        struct.h
        func.c
        func.h
        private_funcs.c
        private_funcs.h
#        test.c
)
