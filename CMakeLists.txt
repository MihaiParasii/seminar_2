cmake_minimum_required(VERSION 3.27)
project(Sem2 C)

set(CMAKE_C_STANDARD 23)

add_executable(Sem2 main.c
        model/struct.h
        view/v_func.h
        view/v_private_func.c
        view/v_func.c
        controller/c_funcs.c
        controller/c_funcs.h
        controller/c_private_funcs.c
        controller/c_private_funcs.h
)
