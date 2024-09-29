//
// Created by jag on 9/29/24.
//

#include "sorting.h"
#include "../header.h"

void nameSort(int dir) {
    if (dir) {
        qsort(students, studentsAmount, sizeof(student), cmpNameAscending);
    } else {
        qsort(students, studentsAmount, sizeof(student), cmpNameDescending);
    }
}

void surnameSort(int dir) {
    if (dir) {
        qsort(students, studentsAmount, sizeof(student), cmpSurnameAscending);
    } else {
        qsort(students, studentsAmount, sizeof(student), cmpSurnameDescending);
    }
}

void heightSort(int dir) {
    if (dir) {
        qsort(students, studentsAmount, sizeof(student), cmpHeightAscending);
    } else {
        qsort(students, studentsAmount, sizeof(student), cmpHeightDescending);
    }
}