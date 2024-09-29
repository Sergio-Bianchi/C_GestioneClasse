//
// Created by jag on 9/29/24.
//

#ifndef C_GESTIONECLASSE_SORTING_H
#define C_GESTIONECLASSE_SORTING_H


/* * Sorting mains */

void nameSort(int dir);

void surnameSort(int dir);

void heightSort(int dir);

/* * Comparisons */
int cmpNameDescending(const void *a, const void *b);

int cmpSurnameDescending(const void *a, const void *b);

int cmpHeightDescending(const void *a, const void *b);

int cmpNameAscending(const void *a, const void *b);

int cmpSurnameAscending(const void *a, const void *b);

int cmpHeightAscending(const void *a, const void *b);


#endif //C_GESTIONECLASSE_SORTING_H
