#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#define MAX_PALAVRAS 10000
#define TAMANHO_MAX 50
#define MAX_PLAYERS 100

typedef struct {
    char nome[50];
    int pontos;
} Jogador;

// Funções auxiliares para tempo e tela
void clockTime(int x) {
    #ifdef _WIN32
        Sleep(x);
    #else
        usleep(x * 1000);
    #endif
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void imprimir(int list[], int MAX) {
    for (int i = 0; i < MAX; i++) {
        printf("| %d ", list[i]);
    }
    printf("|\n\n");
}

// Implementação do Insertion Sort
int Insertion(int MAX, int type) {
    int list[MAX], cha;

    for (int i = 0; i < MAX; i++) {
        list[i] = (rand() % 99) + 1;
    }

    imprimir(list, MAX);

    for (int i = 1; i < MAX; i++) {
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

// Implementação do QuickSort com escolha tradicional do pivô
int apend(int list[], int min, int max, int type, int choice, int *perc) {
    int pivo = (choice == 1) ? list[max] : list[min];
    int i = min - 1;
    (*perc)++;

    for (int j = min; j < max; j++) {
        if ((list[j] <= pivo && type == 1) || (list[j] >= pivo && type == 2)) {
            i++;
            trocar(&list[i], &list[j]);
        }
    }
    trocar(&list[i + 1], &list[max]);
    printf("Percorrida %d = ", *perc);
    imprimir(list, max + 1);
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
    int list[MAX], perc = 0;

    for (int i = 0; i < MAX; i++) {
        list[i] = (rand() % 99) + 1;
    }

    imprimir(list, MAX);
    Quick(list, 0, MAX - 1, type, choice, &perc);
    imprimir(list, MAX);

    return 0;
}

// QuickSort com Mediana de Três
int medianaDeTres(int list[], int esq, int dir) {
    int meio = (esq + dir) / 2;

    if (list[esq] > list[meio]) trocar(&list[esq], &list[meio]);
    if (list[esq] > list[dir]) trocar(&list[esq], &list[dir]);
    if (list[meio] > list[dir]) trocar(&list[meio], &list[dir]);

    trocar(&list[meio], &list[dir]);
    return list[dir];
}

void QuickSortMediana(int list[], int esq, int dir) {
    if (esq < dir) {
        int pi = medianaDeTres(list, esq, dir);
        QuickSortMediana(list, esq, pi - 1);
        QuickSortMediana(list, pi + 1, dir);
    }
}

// Inserção de jogador no ranking ordenado (InsertionSort)
void inserirJogador(Jogador ranking[], int *tamanho, Jogador novoJogador) {
    int i = *tamanho - 1;

    while (i >= 0 && ranking[i].pontos < novoJogador.pontos) {
        ranking[i + 1] = ranking[i];
        i--;
    }

    ranking[i + 1] = novoJogador;
    (*tamanho)++;
}

void imprimirRanking(Jogador ranking[], int tamanho) {
    printf("\n--- Ranking de Jogadores ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %s - %d pontos\n", i + 1, ranking[i].nome, ranking[i].pontos);
    }
    printf("----------------------------\n");
}

// QuickSort para ordenação de palavras
void QuickSortPalavras(char lista[][TAMANHO_MAX], int esq, int dir) {
    if (esq < dir) {
        int pi = esq;
        for (int j = esq + 1; j <= dir; j++) {
            if (strcmp(lista[j], lista[dir]) < 0) {
                pi++;
                char temp[TAMANHO_MAX];
                strcpy(temp, lista[pi]);
                strcpy(lista[pi], lista[j]);
                strcpy(lista[j], temp);
            }
        }
        char temp[TAMANHO_MAX];
        strcpy(temp, lista[pi]);
        strcpy(lista[pi], lista[dir]);
        strcpy(lista[dir], temp);

        QuickSortPalavras(lista, esq, pi - 1);
        QuickSortPalavras(lista, pi + 1, dir);
    }
}

void menu() {
    printf("1 - Metodo Insertion\n");
    printf("2 - Metodo Quick\n");
    printf("3 - QuickSort com Mediana de Tres\n");
    printf("4 - Inserir Jogador no Ranking\n");
    printf("5 - Ordenar Palavras com QuickSort\n");
    printf("0 - Sair\n\n");
}

int main() {
    int choice, num, type, QuickChoice;
    Jogador ranking[MAX_PLAYERS];
    int numJogadores = 0;

    char palavras[MAX_PALAVRAS][TAMANHO_MAX];
    int numPalavras = 0;

    clearScreen();

    do {
        menu();
        printf("Escolha: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Tamanho da lista: ");
                scanf("%d", &num);
                printf("1 - Crescente ou 2 - Decrescente: ");
                scanf("%d", &type);
                Insertion(num, type);
                break;

            case 2:
                printf("Tamanho da lista: ");
                scanf("%d", &num);
                printf("1 - Crescente ou 2 - Decrescente: ");
                scanf("%d", &type);
                printf("1 - Pivo no final ou 2 - Pivo no começo: ");
                scanf("%d", &QuickChoice);
                PreQuick(num, type, QuickChoice);
                break;

            case 3:
                printf("Tamanho da lista: ");
                scanf("%d", &num);
                int list[num];
                for (int i = 0; i < num; i++) list[i] = rand() % 99 + 1;
                imprimir(list, num);
                QuickSortMediana(list, 0, num - 1);
                imprimir(list, num);
                break;

            case 4:
                printf("Nome do jogador: ");
                scanf("%s", ranking[numJogadores].nome);
                printf("Pontos: ");
                scanf("%d", &ranking[numJogadores].pontos);
                inserirJogador(ranking, &numJogadores, ranking[numJogadores]);
                imprimirRanking(ranking, numJogadores);
                break;

            case 5:
                printf("Ordenando palavras...\n");
                QuickSortPalavras(palavras, 0, numPalavras - 1);
                break;

            case 0:
                printf("Saindo...\n");
                break;
        }
    } while (choice != 0);

    return 0;
}