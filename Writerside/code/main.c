#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <header.h>

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
        if (students[i].name[0] != '*') {
            printf("%02d) %20s %20s %8d", i, students[i].name, students[i].surname, students[i].height);
            bckls();
        }
    }
}


void addName() {
    /* Pulisci il buffer di stdin*/
    // TODO, controllare ogni recursive function per il buffer
    fflush(stdin);

    /* Dichiarazione funzioni*/
    char input[20];
    printf("Name (max 20 c):");
    fgets(input, 20, stdin);

    /* Se il nome è più corto di tre caratteri, richiama*/
    if (strlen(input) < 3) {
        printf("Name too short\n");
        addSurname();
        return;
    }
    /* Se una delle lettere del nome non è un carattere alfa, richiama*/
    for (int i = 0; i < 20; ++i) {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        };
        if (!(isalpha(input[i]) || input[i] == ' ')) {
            printf("Please use only alpha characters\n");
            addSurname();
            return;
        }
    }

    /* Inserisci il nome nell'ultimo slot dell'array */
    strcpy(students[studentsAmount].name, input);
    printf("Name added: %s\n", students[studentsAmount].name);
}

void addSurname() {
    /* Pulisci il buffer di stdin*/
    // TODO, controllare ogni recursive function per il buffer
    fflush(stdin);

    /* Dichiarazione funzioni*/
    char input[20];
    printf("Surname (max 20 c):");
    fgets(input, 20, stdin);

    /* Se il nome è più corto di tre caratteri, richiama*/
    if (strlen(input) < 3) {
        printf("Surname too short\n");
        addName();
        return;
    }
    /* Se una delle lettere del nome non è un carattere alfa, richiama*/
    for (int i = 0; i < 20; ++i) {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        };
        if (!(isalpha(input[i]) || input[i] == ' ')) {
            printf("Please use only alpha characters\n");
            addName();
            return;
        }
    }

    /* Inserisci il nome nell'ultimo slot dell'array */
    strcpy(students[studentsAmount].surname, input);
    printf("Surname added: %s\n", students[studentsAmount].surname);
}

void addHeight() {
    /* Pulisci il buffer di stdin*/
    // TODO, controllare ogni recursive function per il buffer
    fflush(stdin);

    /* Dichiarazione funzioni*/
    char input[6];
    int height = 0;

    printf("Height (in cm):");
    fgets(input, 5, stdin);

    for (int i = 0; i < 5; ++i) {
        if (input[i] == '\n') {
            break;
        };
        if (input[i] < '0' || input[i] > '9') {
            printf("Not a valid number\n");
            addHeight();
            return;
        }
    }

    /* Converte l'altezza in numero (ho deciso di gestirmela con gli int alla fine*/
    height = strtol(input, NULL, 10);


#ifdef  EGG
    /* Piccolo easter egg se l'altezza inserita è molto bassa o molto alta*/
    if (height < 100) {
        printf("Are they gnomes? %d cm are not a lot", height);
        addHeight();
        return;
    } else if (height > 300) {
        printf("Are they giants? %d cm are a lot", height);
        addHeight();
        return;
    }
#endif


    students[studentsAmount].height = height;


    /* Inserisci il nome nell'ultimo slot dell'array */
    printf("Height added: %d\n", students[studentsAmount].height);
}

void addStudent() {
    /* Allarga la memoria di students per poter contenere altri studenti. Si potrebbe inserire in un'altra funzione */

    /* Se il numero di studenti è superiore al numero massimo permesso dalla memoria assegnata*/

    if (studentsAmount > maxStudentsMemory) {
        /* Creo una variabile che conterrà in nuovo array*/
        /* Alloco alla variabile nuova lo spazio necessario per contenere il nuovo studente + il buffer predefinito (Se il buffer dovesse essere 0, funziona ugualmente)*/
        student *muppet = malloc((studentsAmount + OVERBUFFER + 1) * sizeof(student));

        /* Copio i dati nel nuovo puntatore */
        for (int i = 0; i < studentsAmount; ++i) {
            muppet[i] = students[i];
        }

        /* Libero il vecchio array dalla memoria e assegna a students l'indirizzo del nuovo spazio di memoria*/
        free(students);
        students = muppet;
        /* Aumenta la variabile degli studenti massimi */
        maxStudentsMemory += (OVERBUFFER + 1);
    }
    /* Dichiarazione variabili input. Potrebbe essere ridotta a una*/
    addName();
    addSurname();
    addHeight();

    studentsAmount++;
}


void editStudent() {
    // TODO, sistemare, commentare, rendere a prova di scemo. Per ora, funziona abbastanza

    char input[4];
    int id = 0;
    printf("Choose a student to edit (Note, IDs could change in new execution. Check them with command print)\n");
    while (1) {
        printf("ID: ");
        fflush(stdin);
        fgets(input, 4, stdin);
        id = strtol(input, NULL, 10);
        if (id < studentsAmount) {
            printf("%02d) %20s %20s %8d\n", id, students[id].name, students[id].surname, students[id].height);
            printf("Is it right [Y/n]? ");
            fflush(stdin);
            fgets(input, 4, stdin);
            if (input[0] == 'n' || input[0] == 'N') {
                editStudent();
                return;
            }
            if (input[0] == 'y' || input[0] == 'Y' || input[0] == '\n') break;
        } else {
            printf("Please enter a valid student ID\n");
            editStudent();
            return;
        }
    }
    printf("Insert new height: ");
    fflush(stdin);
    fgets(input, 4, stdin);
    const int height = strtol(input, NULL, 10);
#ifdef  EGG
    /* Piccolo easter egg se l'altezza inserita è molto bassa o molto alta*/
    if (height < 100) {
        printf("Are they gnomes? %d cm are not a lot", height);
        addHeight();
        return;
    } else if (height > 300) {
        printf("Are they giants? %d cm are a lot", height);
        addHeight();
        return;
    }
#endif

    students[id].height = height;
    printf("%s %s's new height is %d cm\n", students[id].name, students[id].surname, students[id].height);
    fflush(stdin);
}


void deleteStudent() {
    // TODO, sistemare, commentare, rendere a prova di scemo. Per ora, funziona abbastanza

    char input[4];
    int id = 0;
    printf("Choose a student to delete (Note, IDs could change in new execution. Check them with command print)\n");
    while (1) {
        printf("ID: ");
        fflush(stdin);
        fgets(input, 4, stdin);
        id = strtol(input, NULL, 10);
        if (id < studentsAmount) {
            printf("%02d) %20s %20s %8d\n", id, students[id].name, students[id].surname, students[id].height);
            printf("Is it right [Y/n]? ");
            fflush(stdin);
            fgets(input, 4, stdin);
            if (input[0] == 'n' || input[0] == 'N') {
                editStudent();
                return;
            }
            if (input[0] == 'y' || input[0] == 'Y' || input[0] == '\n') break;
        } else {
            printf("Please enter a valid student ID\n");
            editStudent();
            return;
        }
    }
    students[id].name[0] = '*';
    printf("Student deleted\n");

    fflush(stdin);
}

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
    else {
        printf("Not a valid command\n");
    }

    mainLoop(file);

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
