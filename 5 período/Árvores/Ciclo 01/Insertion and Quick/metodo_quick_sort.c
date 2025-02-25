#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX 5

// Função para trocar dois elementos
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    
}

// Função de partição (coloca os menores à esquerda e os maiores à direita do pivô)
int particionar(int arr[], int baixo, int alto) {
    int pivo = arr[alto]; // Escolhemos o último elemento como pivô
    int i = (baixo - 1);

    for (int j = baixo; j < alto; j++) {
        if (arr[j] < pivo) {
            i++;
            trocar(&arr[i], &arr[j]);
            printf("\n\n|");
            for(int i = 0; i < MAX; i++) {
                printf(" %d |", arr[i]);
            }
        }
    }
    trocar(&arr[i + 1], &arr[alto]);
    printf("\n\n|");
    for(int i = 0; i < MAX; i++) {
        printf(" %d |", arr[i]);
    }
    return (i + 1);
}

// Função Quick Sort
void quickSort(int arr[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(arr, baixo, alto);
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

int main() {
    int lista[MAX], numb;
    
    for(int i = 0; i < MAX; i++) {
        printf("Escola um numero para casa %d: \n", i);
        scanf("%d", &numb);
        lista[i] = numb;
    }

    printf("\n\n|");

    for(int i = 0; i < MAX; i++) {
        printf(" %d |", lista[i]);
    }
    
    quickSort(lista, 0, MAX - 1);

    return 0;
}
