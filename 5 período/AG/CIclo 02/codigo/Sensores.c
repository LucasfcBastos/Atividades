#include <stdio.h>
#include <stdlib.h>

typedef struct Leitura {
    int timestamp;
    float valor;
    int sensorID;
} Leitura;

typedef struct Node {
    Leitura leitura;
    struct Node* esquerda;
    struct Node* direita;
} Node;

// Criar novo no
Node* criarNo(Leitura l) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->leitura = l;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Inserir leitura na ABB (ordenado por timestamp)
Node* inserir(Node* raiz, Leitura l) {
    if (raiz == NULL) return criarNo(l);
    if (l.timestamp < raiz->leitura.timestamp)
        raiz->esquerda = inserir(raiz->esquerda, l);
    else if (l.timestamp > raiz->leitura.timestamp)
        raiz->direita = inserir(raiz->direita, l);
    return raiz;
}

// Buscar leituras dentro de um intervalo de tempo
void buscarIntervalo(Node* raiz, int inicio, int fim) {
    if (raiz == NULL) return;
    if (raiz->leitura.timestamp > inicio)
        buscarIntervalo(raiz->esquerda, inicio, fim);
    if (raiz->leitura.timestamp >= inicio && raiz->leitura.timestamp <= fim)
        printf("Timestamp: %d | Valor: %.2f | SensorID: %d\n",
               raiz->leitura.timestamp, raiz->leitura.valor, raiz->leitura.sensorID);
    if (raiz->leitura.timestamp < fim)
        buscarIntervalo(raiz->direita, inicio, fim);
}

// Calcular media das leituras em um intervalo
void mediaIntervalo(Node* raiz, int inicio, int fim, float* soma, int* cont) {
    if (raiz == NULL) return;
    if (raiz->leitura.timestamp > inicio)
        mediaIntervalo(raiz->esquerda, inicio, fim, soma, cont);
    if (raiz->leitura.timestamp >= inicio && raiz->leitura.timestamp <= fim) {
        *soma += raiz->leitura.valor;
        (*cont)++;
    }
    if (raiz->leitura.timestamp < fim)
        mediaIntervalo(raiz->direita, inicio, fim, soma, cont);
}

// Detectar leituras anomalias (fora de faixa)
void detectarAnomalias(Node* raiz, float minValor, float maxValor) {
    if (raiz == NULL) return;
    detectarAnomalias(raiz->esquerda, minValor, maxValor);
    if (raiz->leitura.valor < minValor || raiz->leitura.valor > maxValor) {
        printf("Anomalia detectada - Timestamp: %d | Valor: %.2f | SensorID: %d\n",
               raiz->leitura.timestamp, raiz->leitura.valor, raiz->leitura.sensorID);
    }
    detectarAnomalias(raiz->direita, minValor, maxValor);
}

// Criar leitura
Leitura criarLeitura(int timestamp, float valor, int sensorID) {
    Leitura l;
    l.timestamp = timestamp;
    l.valor = valor;
    l.sensorID = sensorID;
    return l;
}

int main() {
    Node* raiz = NULL;

    // Inserir leituras
    raiz = inserir(raiz, criarLeitura(1000, 25.4, 1));
    raiz = inserir(raiz, criarLeitura(1020, 28.7, 2));
    raiz = inserir(raiz, criarLeitura(1010, 22.3, 1));
    raiz = inserir(raiz, criarLeitura(1030, 30.1, 2));
    raiz = inserir(raiz, criarLeitura(1050, 19.8, 3));

    printf("Leituras entre 1000 e 1040:\n");
    buscarIntervalo(raiz, 1000, 1040);

    float soma = 0;
    int cont = 0;
    mediaIntervalo(raiz, 1000, 1050, &soma, &cont);
    if (cont > 0)
        printf("\nMedia das leituras entre 1000 e 1050: %.2f\n", soma / cont);
    else
        printf("\nNenhuma leitura no intervalo\n");

    printf("\nLeituras anormais (valor < 20.0 ou > 29.0):\n");
    detectarAnomalias(raiz, 20.0, 29.0);

    return 0;
}