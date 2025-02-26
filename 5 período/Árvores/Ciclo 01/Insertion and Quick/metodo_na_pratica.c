#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void printArray(int arr[], int MAX) {
    printf("\n\n|");    

    for(int i = 0; i < MAX; i++) {
        printf(" %d |", arr[i]);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int baixo, int alto) {
    int pivo = arr[alto];
    int i = (baixo - 1);

    for (int j = baixo; j < alto; j++) {
        if (arr[j] < pivo) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[alto]);
    return (i + 1);
}

void quickSort(int arr[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = partition(arr, baixo, alto);
        quickSort(arr, baixo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

int InsertionSort(int MAX) {
    int lista[MAX], numb;

    for(int i = 0; i < MAX; i++) {
        printf("Escola um numero para casa %d: \n", i);
        scanf("%d", &numb);
        lista[i] = numb;
    }
    
    for (int i = 1; i < MAX; i++) {
        int chave = lista[i]; 
        int j = i - 1;

        while (j >= 0 && lista[j] > chave) {
            lista[j + 1] = lista[j];
            j = j - 1;
        }
        lista[j + 1] = chave;
    }

    return 0;
}

int main() {
    int numb;

    clearScreen();

    printf("Digita a quantidade de dados: \n");
    scanf("%d", &numb);
    
    clearScreen();

    printf("Bubble Sort = %d dados Aleatorios\n\n", numb);
    BubbleSort(numb);
    
    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

    printf("\nSelection Sort = %d dados Aleatorios\n\n", numb);
    SelectionSort(numb);

    return 0;
}