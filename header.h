//
// Created by jag on 9/19/24.
//

#ifndef C_GESTIONECLASSE_HEADER_H
#define C_GESTIONECLASSE_HEADER_H

#include <stdio.h>

#define OVERBUFFER 10

// Abilita gli easter eggs
#define EGG

#define bckls() printf("\n")

typedef struct {
    char name[21];
    char surname[21];
    int height;
} student;

int readData(FILE *fp);

int countLines(FILE *fp);

int strToInt(char *string);

int mainLoop(char *file);

void printHelp();

void printStudents();

void addStudent();

void addName();

void addSurname();

void addHeight();


void editStudent();

void deleteStudent();

void saveToFile(const char *file);

void clrscr();

#endif //C_GESTIONECLASSE_HEADER_H
