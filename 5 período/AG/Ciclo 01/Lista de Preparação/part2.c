#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#ifdef _WIN32
    #include <windows.h>
#endif

void clockTime(int x) {
    #ifdef _WIN32
        Sleep(x); // Windows
    #else
        usleep(x * 1000); // Linux
    #endif
}

void clearScreen() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux
    #endif
}

void trocou(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void imprimir(int list[], int MAX){
    for(int i = 0; i < MAX - 1; i++){
        printf("| %d ", list[i]);
    }
    printf("|\n\n");
}

int Insertion(int MAX, int type) {
    int list[MAX], cha;

    for(int i = 0; i < MAX; i++){
        list[i] = (rand() % 99) + 1;
    }

    imprimir(list, MAX);

    for(int i = 0; i < MAX-1; i++){
        cha = list[i];
        int j = i - 1;

        while (j >= 0 && ((list[j] > cha && type == 1) || (list[j] < cha && type == 2))) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = cha;

        imprimir(list, MAX);

    }

    return 0;
}

int apend(int list[], int min, int max, int type, int choice, int *perc) {
    int pivo;
    if (choice == 1) {
        pivo = list[max];
    } else if (choice == 2) {
        pivo = list[min];
    }
    int i = min - 1;
    (*perc)++;

    for (int j = min; j < max; j++) {
        if (list[j] <= pivo && type == 1) {
            i++;
            trocou(&list[i], &list[j]);
        } else if (list[j] >= pivo && type == 2) {
            i++;
            trocou(&list[i], &list[j]);
        }
    }
    trocou(&list[i + 1], &list[max]);
    printf("percorrida %d = ", *perc);
    imprimir(list, max+1);
    return i + 1;
}

void Quick(int list[], int min, int max, int type, int choice, int *perc) {
    if (min < max) {
        int pi = apend(list, min, max, type, choice, perc);
        Quick(list, min, pi - 1, type, choice, perc);
        Quick(list, pi + 1, max, type, choice, perc);
    }
}

int PreQuick(int MAX, int type, int choice) {
    int list[MAX];
    int perc = 0;

    for(int i = 0; i < MAX; i++){
        list[i] = (rand() % 99) + 1;
    }

    imprimir(list, MAX);

    Quick(list, 0, MAX - 1, type, choice, &perc);

    imprimir(list, MAX);

    return 0;
}

void menu() {
    printf("1 - Metodo Insertion\n");
    printf("2 - Metodo Quick\n");
    printf("0 - Sair\n\n");
}

int main() {
    int choice, num, type, QuickChoice;
    clearScreen();

    do {
        menu();
        printf("Escolha\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("\n=-=-=-=-= INSERTION =-=-=-=-=\n\n");
            printf("Escolha quanto elementos tem na lista: \n");
            scanf("%d", &num);
            printf("1 - Cresente ou 2 - Decresente: \n");
            scanf("%d", &type);
            printf("\n");
            Insertion(num, type);
            clockTime(10000);
            clearScreen();
            break;
        case 2:
            printf("\n=-=-=-=-= QUICK =-=-=-=-=\n\n");
            printf("Escolha quanto elementos tem na lista: \n");
            scanf("%d", &num);
            printf("1 - Cresente ou 2 - Decresente: \n");
            scanf("%d", &type);
            printf("1 - Pivo no final ou 2 - Pivo no comeco: \n");
            scanf("%d", &QuickChoice);
            printf("\n");
            PreQuick(num, type, QuickChoice);
            clockTime(10000);
            clearScreen();
            break;
        case 0:
            printf("\nSAINDO\n");
            clockTime(2500);
            clearScreen();
            break;
        default:
            clearScreen();
            printf("\n\tOPCAO INVALIDA\n");
            clockTime(2500);
            clearScreen();
            break;
        }

    } while (choice != 0);

    return 0;
}