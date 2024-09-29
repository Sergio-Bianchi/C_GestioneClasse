//
// Created by jag on 9/29/24.
//

#ifndef C_GESTIONECLASSE_MANAGE_FILE_H
#define C_GESTIONECLASSE_MANAGE_FILE_H

#include "stdio.h"
#include "../header.h"

void saveToFile(const char *file);

int readData(FILE *fp);

int countLines(FILE *fp);


#endif //C_GESTIONECLASSE_MANAGE_FILE_H
