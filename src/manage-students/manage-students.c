//
// Created by jag on 9/29/24.
//

#include "manage-students.h"

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
        }
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
        printf("Are they gnomes? %d cm are not a lot\n", height);
        addHeight();
        return;
    } else if (height > 300) {
        printf("Are they giants? %d cm are a lot\n", height);
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
        printf("Are they gnomes? %d cm are not a lot\n", height);
        addHeight();
        return;
    } else if (height > 300) {
        printf("Are they giants? %d cm are a lot\n", height);
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

        /* Se lo studente selezionato è eliminato, prova a prendere il successivo. Se arriva alla fine, fallisce. Comodo soprattutto
         * se si voglioni eliminare i primi studenti e non si vuole sempre inserire l'ID
         * */
        while (students[id].name[0] == '*') {
            id++;
            if (id > studentsAmount) {
                printf("Please enter a valid student ID\n");
                editStudent();
                return;
            }
        }
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