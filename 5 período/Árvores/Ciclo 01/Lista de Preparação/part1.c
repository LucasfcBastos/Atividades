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

int CompareSaida(int MAX, int type) {
    int list[MAX], listCopy[MAX], tro, pos, ida;

    for(int i = 0; i < MAX; i++){
        list[i] = (rand() % 99) + 1;
    }
    
    imprimir(list, MAX);

    for(int i = 0; i < MAX; i++){
        listCopy[i] = list[i];
    }

    ida = 0;

    do {
        tro = 0;
        ida++;
        for(int i = 0; i < MAX-1; i++){
            if(list[i] > list[i+1] && type == 1){
                trocou(&list[i], &list[i+1]);
                tro = 1;
            } else if(list[i] < list[i+1] && type == 2){
                trocou(&list[i], &list[i+1]);
                tro = 1;
            }
        }
    } while (tro);

    printf("A lista com %d elementos, se utilizando do metodo Bubble, percorreu a lista %d vezes\n\n", MAX, ida);

    for(int i = 0; i < MAX; i++){
        listCopy[i] = list[i];
    }

    ida = 0;

    for(int i = 0; i < MAX-1; i++){
        pos = i;
        ida++;

        for(int j = i + 1; j < MAX; j++){
            if(list[j] < list[pos] && type == 1) {
                pos = j;
            } else if(list[j] > list[pos] && type == 2) {
                pos = j;
            }
        }

        if(pos != i) {
            trocou(&listCopy[i], &listCopy[pos]);
        }
    }

    printf("A lista com %d elementos, se utilizando do metodo Selection, percorreu a lista %d vezes\n\n", MAX, ida);

    return 0;

}

int Bubble(int MAX, int type) {
    int list[MAX], tro;

    for(int i = 0; i < MAX; i++){
        list[i] = (rand() % 99) + 1;
    }

    imprimir(list, MAX);

    do {
        tro = 0;
        for(int i = 0; i < MAX-1; i++){
            if(list[i] > list[i+1] && type == 1){
                trocou(&list[i], &list[i+1]);
                tro = 1;
            } else if(list[i] < list[i+1] && type == 2){
                trocou(&list[i], &list[i+1]);
                tro = 1;
            }
        }

        imprimir(list, MAX);

    } while (tro);

    return 0;
}

int Selection(int MAX, int type) {
    int list[MAX], pos;

    for(int i = 0; i < MAX; i++){
        list[i] = (rand() % 99) + 1;
    }

    imprimir(list, MAX);

    for(int i = 0; i < MAX-1; i++){
        pos = i;

        for(int j = i+1; j < MAX; j++){
            if(list[j] < list[pos] && type == 1) {
                pos = j;
            } else if(list[j] > list[pos] && type == 2) {
                pos = j;
            }
        }

        if (pos != i){
            trocou(&list[i], &list[pos]);
        }

        imprimir(list, MAX);

    }

    return 0;
}

int CompareTempo(int MAX, int type) {
    srand(time(NULL));
    int list[MAX], listCopy[MAX], tro, pos;

    for(int i = 0; i < MAX; i++){
        list[i] = (rand() % 99) + 1;
    }
    
    imprimir(list, MAX);

    for(int i = 0; i < MAX; i++){
        listCopy[i] = list[i];
    }

    clock_t start = clock();

    do {
        tro = 0;
        for(int i = 0; i < MAX-1; i++){
            if(list[i] > list[i+1] && type == 1){
                trocou(&list[i], &list[i+1]);
                tro = 1;
            } else if(list[i] < list[i+1] && type == 2){
                trocou(&list[i], &list[i+1]);
                tro = 1;
            }
        }
    } while (tro);

    clock_t end = clock();
    double timeB = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("A lista com %d elementos, se utilizando do metodo Bubble, gastou %.3f milisegundos\n\n", MAX, timeB);

    for(int i = 0; i < MAX; i++){
        listCopy[i] = list[i];
    }

    start = clock();

    for(int i = 0; i < MAX-1; i++){
        pos = i;

        for(int j = i + 1; j < MAX; j++){
            if(list[j] < list[pos] && type == 1) {
                pos = j;
            } else if(list[j] > list[pos] && type == 2) {
                pos = j;
            }
        }

        if(pos != i) {
            trocou(&listCopy[i], &listCopy[pos]);
        }
    }

    end = clock();
    double timeS = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("A lista com %d elementos, se utilizando do metodo Selection, gastou %.3f milisegundos\n\n", MAX, timeS);

    return 0;

}

void menu() {
    printf("1 - Metodo Bubble\n");
    printf("2 - Metodo Selection\n");
    printf("3 - Comparacao dos Metodos\n");
    printf("4 - Tempo de Metodos\n");
    printf("0 - Sair\n\n");
}

int main() {
    int choice, num, type;
    clearScreen();

    do {
        menu();
        printf("Escolha\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("\n=-=-=-=-= BUBBLE =-=-=-=-=\n\n");
            printf("Escolha quanto elementos tem na lista: \n");
            scanf("%d", &num);
            printf("1 - Cresente ou 2 - Decresente: \n");
            scanf("%d", &type);
            printf("\n");
            Bubble(num, type);
            clockTime(10000);
            clearScreen();
            break;
        case 2:
            printf("\n=-=-=-=-= SELECTION =-=-=-=-=\n\n");
            printf("Escolha quanto elementos tem na lista: \n");
            scanf("%d", &num);
            printf("1 - Cresente ou 2 - Decresente: \n");
            scanf("%d", &type);
            printf("\n");
            Selection(num, type);
            clockTime(10000);
            clearScreen();
            break;
        case 3:
            printf("\n=-=-=-=-= COMPARANDO PERCORRIDA =-=-=-=-=\n\n");
            printf("Escolha quanto elementos tem na lista: \n");
            scanf("%d", &num);
            printf("1 - Cresente ou 2 - Decresente: \n");
            scanf("%d", &type);
            printf("\n");
            CompareSaida(num, type);
            clockTime(10000);
            clearScreen();
            break;
        case 4:
            printf("\n=-=-=-=-= COMPARANDO TEMPO =-=-=-=-=\n\n");
            printf("Escolha quanto elementos tem na lista: \n");
            scanf("%d", &num);
            printf("1 - Cresente ou 2 - Decresente: \n");
            scanf("%d", &type);
            printf("\n");
            CompareTempo(num, type);
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