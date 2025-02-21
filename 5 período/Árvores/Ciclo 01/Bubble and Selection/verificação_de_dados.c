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

void looding(char* text) {
    printf("%s", text);
    for(int i = 0; i < 3; i++) {
        clockTime(1000);
        printf(".");
    }
    clockTime(1000);
    printf("\n\n");
}

void clearScreen() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux
    #endif
}

int BubbleSort(int MAX) {
    int lista[MAX];

    srand(time(NULL));

    looding("REPRESENTANDO DADOS");

    for(int i = 0; i < MAX; i++) {
        lista[i] = (rand() % 99) + 1;
    }

    for(int i = 0; i < MAX; i++) {
        printf("| %d ", lista[i]);
    }
    printf("|\n\n");

    int trocou, movimento = 0, comparacao = 0;

    looding("CALCULANDO E ORDENANDO");

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

    looding("CALCULANDO DESENPENHO");

    printf("\tResultados da Ordenacao\n");
    printf("Tempo: %.6f segundos\n", tempo_execucao);
    printf("Comparacoes: %d\n", comparacao);
    printf("Movimentos: %d\n\n", movimento);

    looding("INSERIDO RESULTADO NO ARQUIVO");

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

    looding("SALVANDO ARQUIVO");

    printf("arquivo salvo com sucesso\n");

    return 0;
}

int SelectionSort(int MAX) {
    int lista[MAX];

    srand(time(NULL));
    
    looding("REPRESENTANDO DADOS");

    for(int i = 0; i < MAX; i++) {
        lista[i] = (rand() % 99) + 1;
    }

    for(int i = 0; i < MAX; i++) {
        printf("| %d ", lista[i]);
    }
    printf("|\n\n");

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

    looding("CALCULANDO DESENPENHO");

    printf("\tResultados da Ordenacao\n");
    printf("Tempo: %.6f segundos\n", tempo_execucao);
    printf("Comparacoes: %d\n", comparacao);
    printf("Movimentos: %d\n\n", movimento);

    looding("INSERIDO RESULTADO NO ARQUIVO");

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

    looding("SALVANDO ARQUIVO");

    printf("arquivo salvo com sucesso\n\n");

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