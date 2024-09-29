#include "header.h"


int maxStudentsMemory = 0;
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
            maxStudentsMemory = studentsAmount + OVERBUFFER;
        }
    } else {
        // Assegna uno spazio in memoria a students per tanti studenti quanti presenti nel file, + un buffer predefinito
        studentsAmount = countLines(fp);
        students = malloc((studentsAmount + OVERBUFFER) * sizeof(student));
        maxStudentsMemory = studentsAmount - 1 + OVERBUFFER;
        readData(fp);
    }

    mainLoop(argv[1]);
}

/* Ciclo principale dell'applicazione */
int mainLoop(char *file) {
    printf("C_GestioneClasse (m for help): ");
    char command[20];
    fflush(stdin);
    fgets(command, 20, stdin);
    if (!strcmp(command, "m\n")) printHelp();
    else if (!strcmp(command, "q\n")) return 0;
    else if (!strcmp(command, "cl\n")) clrscr();
    else if (!strcmp(command, "p\n")) printStudents();
    else if (!strcmp(command, "e\n")) editStudent();
    else if (!strcmp(command, "w\n")) saveToFile(file);
    else if (!strcmp(command, "a\n")) addStudent();
    else if (!strcmp(command, "d\n")) deleteStudent();
    else if (!strcmp(command, "sNd\n")) nameSort(0);
    else if (!strcmp(command, "sNa\n")) nameSort(1);
    else if (!strcmp(command, "sSd\n")) surnameSort(0);
    else if (!strcmp(command, "sSa\n")) surnameSort(1);
    else if (!strcmp(command, "sHd\n")) heightSort(0);
    else if (!strcmp(command, "sHa\n")) heightSort(1);
    else {
        printf("Not a valid command\n");
    }

    mainLoop(file);

    return 0;
}
