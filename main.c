#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <header.h>


int studentsAmount = 0;


int main(int argc, char *argv[]) {
    FILE *fp;
    student *students = NULL;
    // Exit if no file is provided
    if (argc < 2) {
        printf("Provide the file you want to edit or create\n");
        return -1;
    }

    // Try to open the file given
    fp = fopen(argv[1], "r");

    // If the file doesn't exist, create new one
    if (fp == NULL) {
        fp = fopen(argv[1], "w");
        if (fp == NULL) {
            printf("Failed to create/open file. Verify that the directory exists and it's correct\n");
            return -2;
        } else {
            printf("File created \n");
            students = malloc((studentsAmount + OVERBUFFER) * sizeof(student));
        }
    } else {
        // Assegna uno spazio in memoria a students per tanti studenti quanti presenti nel file, + un buffer predefinito
        studentsAmount = countLines(fp);
        students = malloc((studentsAmount + OVERBUFFER) * sizeof(student));
        readData(fp, students);
    }

    /* Da qui in avanti, possiamo passare al management del tutto */
/*    for (int k = 0; k <= studentsAmount; ++k) {
        if (isalpha(students[k].name[0])) {
            printf("%s\n", students[k].name);
        }
    }*/
    mainLoop();
}

void printHelp() {
    printf("\nHelp: \n\n"
           "    p       Print current class\n"
           "    w       Save class to file\n"
           "    m       Print this menu\n"
           "    cl     Clear the screen\n"
           "    e [id]  Edit student\n"
           "    a [id]  Add a student\n"
           "    d [id]  Delete a student\n"
           "    q       Exit\n");
}

int mainLoop() {
    printf("C_GestioneClasse (m for help): ");
    char command[20];
    fgets(command, 20, stdin);
    if (!strcmp(command, "m\n")) printHelp();
    else if (!strcmp(command, "q\n")) return 0;
    else if (!strcmp(command, "cl\n")) clrscr();
    else if (!strcmp(command, "p\n")) printf("Command PRINT in progress\n");
    else if (!strcmp(command, "e\n")) printf("Command EDIT called. These is a lot to do here\n");
    else if (!strcmp(command, "w\n")) printf("Command WRITE called. These is a lot to do here\n");
    else if (!strcmp(command, "a\n")) printf("Command ADD called. These is a lot to do here\n");
    else if (!strcmp(command, "d\n")) printf("Command DELETE called. These is a lot to do here\n");
    else {
        printf("Not a valid command\n");
    }

    mainLoop();

    return 0;
}

void clrscr() {
    system("@cls||clear\n");
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


int readData(FILE *fp, student *students) {

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
                // TODO Opzionale, non serve per forza convertire il testo. Deciderò più tardi
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
