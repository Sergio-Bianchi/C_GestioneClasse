cmake_minimum_required(VERSION 3.27)
project(C_GestioneClasse C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(C_GestioneClasse
        src/main.c
        src/header.h
        src/sorting/sorting.c
        src/sorting/compare.c
        src/sorting/sorting.h
        src/manage-file/manage-file.h
        src/main.c
        src/utils/utils.c
        src/utils/utils.h
        src/manage-file/manage-file.c
        src/manage-students/manage-students.c
        src/manage-students/manage-students.h
        src/manage-interaction/manage-interaction.c
        src/manage-interaction/manage-interaction.h
)
