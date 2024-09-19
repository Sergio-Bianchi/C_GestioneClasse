cmake_minimum_required(VERSION 3.27)
project(C_GestioneClasse C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(C_GestioneClasse
        main.c
        header.h
)
