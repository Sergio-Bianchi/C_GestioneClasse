//
// Created by jag on 9/19/24.
//

#ifndef C_GESTIONECLASSE_HEADER_H
#define C_GESTIONECLASSE_HEADER_H
#include <stdio.h>
#define OVERBUFFER 10

typedef struct {
    char name[20];
    char surname[20];
    int height;

} student;

int readData(FILE * fp, student * students);
int countLines(FILE * fp);
int strToInt(char * string);
int mainLoop();

void printHelp();


void clrscr();
#endif //C_GESTIONECLASSE_HEADER_H
