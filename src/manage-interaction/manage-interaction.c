//
// Created by jag on 9/29/24.
//

#include "manage-interaction.h"


void printHelp() {
    printf("\nHelp: \n\n"
           "    p       Print current class\n"
           "    w       Save class to file\n"
           "    sXx     Sort students [X: N(ame), S(urname), H(eight) | x: d(escending), a(scending)]\n"
           "    m       Print this menu\n"
           "    cl      Clear the screen\n"
           "    e       Edit student\n"
           "    a       Add a student\n"
           "    d       Delete a student\n"
           "    q       Exit\n");
}

/* 3mpa la tabella caricata in RAM*/
void printStudents() {
    /* Stampa i nomi delle colonne allineati*/
    printf("%-3s %20s %20s %8s\n\n", "ID", "NAME", "SURNAME", "HEIGHT");
    /* Stampa tutte le colonne*/
    for (int i = 0; i < studentsAmount; i++) {
        if (students[i].name[0] != '*') {
            printf("%02d) %20s %20s %8d", i, students[i].name, students[i].surname, students[i].height);
            bckls();
        }
    }
}