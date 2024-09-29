//
// Created by jag on 9/19/24.
//

#ifndef C_GESTIONECLASSE_HEADER_H
#define C_GESTIONECLASSE_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* * Includes all files headers*/

#include "sorting/sorting.h"
#include "utils/utils.h"
#include "manage-file/manage-file.h"
#include "manage-students/manage-students.h"
#include "manage-interaction/manage-interaction.h"

#define OVERBUFFER 10

// Abilita gli easter eggs
#define EGG

#define bckls() printf("\n")

typedef struct {
    char name[21];
    char surname[21];
    int height;
} student;


extern int maxStudentsMemory;
extern int studentsAmount;
extern student *students;


int mainLoop(char *file);


#endif //C_GESTIONECLASSE_HEADER_H
