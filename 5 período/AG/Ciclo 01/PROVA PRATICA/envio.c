#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 4

void exibir(float list[]) {
    for(int i = 0; i < MAX; i++) {
        if (list[i] == 50.00) {
            printf("| Carregador = %.2f ", list[i]);
        } else if (list[i] == 150.50) {
            printf("| Fone = %.2f ", list[i]);
        } else if (list[i] == 270.00) {
            printf("| Celular = %.2f ", list[i]);
        } else if (list[i] == 300.00) {
            printf("| Notebbok = %.2f ", list[i]);
        } 
    }
    printf("|\n\n");
}

void trocar(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

int Bubble(float lista[]){
    srand(time(NULL));
    int tro;
    
    clock_t inicio = clock();
    do {
        tro = 0;
        for(int i = 0; i < MAX - 1; i++) {
            if (lista[i] > lista[i + 1]) {
                trocar(&lista[i], &lista[i + 1]);
                tro = 1;
            }
        }
    } while (tro);
    clock_t fim = clock();

    printf("Ordenacao Cresente (Bubble Sort): ");
    exibir(lista);

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    printf("Tempo de execucao (Bubble Sort): %.3f ms\n\n", tempo);

    return 0;

}

int Selection(float lista[]){
    srand(time(NULL));
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
            trocar(&lista[i], &lista[pos]);
        }
    }
    clock_t fim = clock();

    printf("Ordenacao Cresente (Selection Sort): ");
    exibir(lista);

    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    printf("Tempo de execucao (Selection Sort): %.3f ms \n\n", tempo);

    return 0;

}

int main() {
    float preco[] = {300.00, 150.50, 50.00, 270.00};
    float ListCopy[MAX];

    printf("\n");
    exibir(preco);

    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    for(int i = 0; i < MAX; i++){
        ListCopy[i] = preco[i];
    }

    Bubble(ListCopy);

    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    for(int i = 0; i < MAX; i++){
        ListCopy[i] = preco[i];
    }

    Selection(ListCopy);
    
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");

    return 0;
}