//
// Created by jag on 9/29/24.
//


#include "manage-file.h"


void saveToFile(const char *file) {
    /* Apri il file specificato all'inzio in write*/
    FILE *fp = fopen(file, "w");
    /* Scrivi tutto il contenuto dell'array students*/
    for (int i = 0; i < studentsAmount; ++i) {
        if (students[i].name[0] != '*') {
            fprintf(fp, "%s;%s;%d;\n", students[i].name, students[i].surname, students[i].height);
        }
    }
}

int readData(FILE *fp) {
    // Riparti dall'inizio del file (siamo arrivati in fondo dopo aver chiamato la funzione countLines
    rewind(fp);

    char buffer[100];
    int i = 0;

    // ... Per ogni riga nel file
    while (fgets(buffer, 100, fp)) {
        // Usa strtok per dividere il contenuto della stringa
        char *token = strtok(buffer, ";");
        // ...Per tre volte, come le colonne, associa il valore della colonna al giusto slot nella struct
        for (int j = 0; j <= 2; j++) {
            if (j == 0) {
                strcpy(students[i].name, token);
            }
            if (j == 1) {
                strcpy(students[i].surname, token);
            }
            if (j == 2) {
                // Strtol converte il testo in numero per facilitarne la modifica
                int height = strtol(token, NULL, 10);
                students[i].height = height;
            }
            // Avanza con strtok alla prossima colonna
            token = strtok(NULL, ";");
        }
        i++;
    }


    return 0;
}


// Count up lines in a file
int countLines(FILE *fp) {
    int output = 0;
    char ch;
    while (!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n') {
            output++;
        }
    }
    return output;
}


