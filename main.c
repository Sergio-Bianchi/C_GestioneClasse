#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <header.h>


int studentsAmount = 0;
student *students = NULL;


int main(int argc, char *argv[]) {
    FILE *fp;
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
        readData(fp);
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
           "    cl      Clear the screen\n"
           "    e [id]  Edit student\n"
           "    a       Add a student\n"
           "    d [id]  Delete a student\n"
           "    q       Exit\n");
}

/* Stampa la tabella caricata in RAM*/
void printStudents() {
    /* Stampa i nomi delle colonne allineati*/
    printf("%-3s %20s %20s %8s\n\n", "ID", "NAME", "SURNAME", "HEIGHT");
    /* Stampa tutte le colonne*/
    for (int i = 0; i < studentsAmount; i++) {
        printf("%02d) %20s %20s %8d", i, students[i].name, students[i].surname, students[i].height);
        bckls();
    }
}


void addName() {
    char input[20];
    printf("Name (max 20 c):");
    fgets(input, 20, stdin);

    /* Se il nome è più corto di tre caratteri, richiama*/
    if (strlen(input) < 3) {
        printf("Name length too short");
        addName();
    }

    /* Se una delle lettere del nome non è un carattere alfa, richiama*/
    for (int i = 0; i < 20; ++i) {
        if (!isalpha(input[i])) {
            printf("Please use only alpha characters");
            addName();
        }
    }

    strcpy(students[studentsAmount].name, input);
}

void addStudent() {
    /* Dichiarazione variabili input. Potrebbe essere ridotta a una*/

    while (1) {

    }

    printf("Surname (max 20 c):");
    fgets(surname, 20, stdin);
    printf("Height (cm):");
    fgets(height, 5, stdin);


}


/* Ciclo principale dell'applicazione */

int mainLoop() {
    printf("C_GestioneClasse (m for help): ");
    char command[20];
    fgets(command, 20, stdin);
    if (!strcmp(command, "m\n")) printHelp();
    else if (!strcmp(command, "q\n")) return 0;
    else if (!strcmp(command, "cl\n")) clrscr();
    else if (!strcmp(command, "p\n")) printStudents();
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
