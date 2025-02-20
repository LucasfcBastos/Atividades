#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int BubbleSort(int MAX) {
    int lista[MAX];

    srand(time(NULL));

    for(int i = 0; i < MAX; i++) {
        lista[i] = (rand() % 99) + 1;
    }

    int trocou, movimento = 0, comparacao = 0;

    clock_t inicio = clock();

    do {
        trocou = 0;
        for(int i = 0; i < MAX - 1; i++) {
            comparacao += 1;
            if (lista[i] > lista[i + 1]) {
                int temp = lista[i];
                lista[i] = lista[i + 1];
                lista[i + 1] = temp;
                movimento += 1;
                trocou = 1;
            }
        }
    } while (trocou);

    clock_t fim = clock();
    double tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    char nome_arquivo[50];
    sprintf(nome_arquivo, "resultado_Bubble_com_%d.txt", MAX);

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "Resultados da Ordenação\n");
    fprintf(arquivo, "-----------------------\n");
    fprintf(arquivo, "Tempo: %.6f segundos\n", tempo_execucao);
    fprintf(arquivo, "Comparações: %d\n", comparacao);
    fprintf(arquivo, "Movimentos: %d\n", movimento);

    fclose(arquivo);

    return 0;
}

int SelectionSort(int MAX) {
    int lista[MAX];

    srand(time(NULL));

    for(int i = 0; i < MAX; i++) {
        lista[i] = (rand() % 99) + 1;
    }

    int posicao, temp, movimento = 0, comparacao = 0;

    clock_t inicio = clock();
    
    for(int i = 0; i < MAX - 1; i++) {
        posicao = i;
        
        for(int j = i + 1; j < MAX; j++) {
            if (lista[j] < lista[posicao]) {
                posicao = j;
                comparacao += 1;
            }
        }

        if (posicao != i) {
            temp = lista[i];
            lista[i] = lista[posicao];
            lista[posicao] = temp;
            movimento += 1;
        }

    }

    clock_t fim = clock();
    double tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    char nome_arquivo[50];
    sprintf(nome_arquivo, "resultado_Selection_com_%d.txt", MAX);

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "Resultados da Ordenação\n");
    fprintf(arquivo, "-----------------------\n");
    fprintf(arquivo, "Tempo: %.6f segundos\n", tempo_execucao);
    fprintf(arquivo, "Comparações: %d\n", comparacao);
    fprintf(arquivo, "Movimentos: %d\n", movimento);

    fclose(arquivo);

    return 0;
}


int main() {
    printf("Bubble Sort = 100 dados Aleatorios");
    BubbleSort(100);
    printf("\n\nBubble Sort = 1000 dados Aleatorios");
    BubbleSort(1000);
    printf("\n\nBubble Sort = 10000 dados Aleatorios");
    BubbleSort(10000);
    printf("\n\nSelection Sort = 100 dados Aleatorios");
    SelectionSort(100);
    printf("\n\nSelection Sort = 1000 dados Aleatorios");
    SelectionSort(1000);
    printf("\n\nSelection Sort = 10000 dados Aleatorios");
    SelectionSort(10000);

    return 0;
}