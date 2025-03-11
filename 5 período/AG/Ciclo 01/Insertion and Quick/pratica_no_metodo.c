#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para trocar dois elementos
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para imprimir o array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Implementação do InsertionSort
void insertionSort(int arr[], int size, int *comparisons, int *swaps) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        (*comparisons)++;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            (*swaps)++;
        }
        arr[j + 1] = key;
    }
}

// Função auxiliar para QuickSort - Particionamento
int partition(int arr[], int low, int high, int *comparisons, int *swaps) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        (*comparisons)++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
            (*swaps)++;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    (*swaps)++;
    return (i + 1);
}

// Implementação do QuickSort
void quickSort(int arr[], int low, int high, int *comparisons, int *swaps) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons, swaps);
        quickSort(arr, low, pi - 1, comparisons, swaps);
        quickSort(arr, pi + 1, high, comparisons, swaps);
    }
}

// Função para preencher um array com valores aleatórios
void fillArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }
}

// Função para copiar um array
void copyArray(int src[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int main() {
    srand(time(NULL));
    int sizes[] = {10, 100, 1000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        int arr[size], arrCopy[size];
        fillArray(arr, size);

        printf("\nTamanho do array: %d\n", size);

        // Teste do InsertionSort
        copyArray(arr, arrCopy, size);
        int insertionComparisons = 0, insertionSwaps = 0;
        clock_t start = clock();
        insertionSort(arrCopy, size, &insertionComparisons, &insertionSwaps);
        clock_t end = clock();
        double insertionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("InsertionSort - Tempo: %.6f s | Comparacoes: %d | Trocas: %d\n", insertionTime, insertionComparisons, insertionSwaps);

        // Teste do QuickSort
        copyArray(arr, arrCopy, size);
        int quickComparisons = 0, quickSwaps = 0;
        start = clock();
        quickSort(arrCopy, 0, size - 1, &quickComparisons, &quickSwaps);
        end = clock();
        double quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("QuickSort - Tempo: %.6f s | Comparacoes: %d | Trocas: %d\n", quickTime, quickComparisons, quickSwaps);
    }
    return 0;
}