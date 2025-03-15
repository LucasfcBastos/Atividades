#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 4

void exibir(float list[], char listC[MAX][20]) {
    for(int i = 0; i < MAX; i++) {
        printf("| %s = %.2f ", listC[i], list[i]);
    }
    printf("|\n\n");
}

void trocarFloat(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

void trocarChar(char a[20], char b[20]) {
    char temp[20];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

void Bubble(float lista[], char listC[MAX][20]){
    int tro;
    
    clock_t inicio = clock();
    do {
        tro = 0;
        for(int i = 0; i < MAX - 1; i++) {
            if (lista[i] > lista[i + 1]) {
                trocarFloat(&lista[i], &lista[i + 1]);
                trocarChar(listC[i], listC[i + 1]);
                tro = 1;
            }
        }
    } while (tro);
    clock_t fim = clock();

    printf("Ordenacao Crescente (Bubble Sort): ");
    exibir(lista, listC);

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    printf("Tempo de execucao (Bubble Sort): %.3f ms\n\n", tempo);
}

void Selection(float lista[], char listC[MAX][20]){
    int pos;
    
    clock_t inicio = clock();
    for(int i = 0; i < MAX - 1; i++) {
        pos = i;
        
        for(int j = i + 1; j < MAX; j++) {
            if (lista[j] < lista[pos]) {
                pos = j;
            }
        }

        if (pos != i) {
            trocarFloat(&lista[i], &lista[pos]);
            trocarChar(listC[i], listC[pos]);
        }
    }
    clock_t fim = clock();

    printf("Ordenacao Crescente (Selection Sort): ");
    exibir(lista, listC);

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    printf("Tempo de execucao (Selection Sort): %.3f ms \n\n", tempo);
}

int main() {
    float preco[] = {300.00, 150.50, 50.00, 270.00}, ListCopyFloat[MAX];
    char nome[MAX][20] = {"Notebook", "Fone", "Carregador", "Celular"}, ListCopyChar[MAX][20];

    printf("\nLista original:\n");
    exibir(preco, nome);

    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    for(int i = 0; i < MAX; i++){
        ListCopyFloat[i] = preco[i];
        strcpy(ListCopyChar[i], nome[i]);
    }

    Bubble(ListCopyFloat, ListCopyChar);

    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    for(int i = 0; i < MAX; i++){
        ListCopyFloat[i] = preco[i];
        strcpy(ListCopyChar[i], nome[i]);
    }

    Selection(ListCopyFloat, ListCopyChar);
    
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    return 0;
}
