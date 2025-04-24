#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarefa {
    char descricao[100];
    int data_vencimento; // formato yyyymmdd
    char prioridade[10]; // baixa, media, alta
} Tarefa;

typedef struct Node {
    Tarefa tarefa;
    struct Node* esquerda;
    struct Node* direita;
} Node;

Node* criarNo(Tarefa t) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->tarefa = t;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

Node* inserir(Node* raiz, Tarefa t) {
    if (raiz == NULL) return criarNo(t);
    if (t.data_vencimento < raiz->tarefa.data_vencimento)
        raiz->esquerda = inserir(raiz->esquerda, t);
    else
        raiz->direita = inserir(raiz->direita, t);
    return raiz;
}

void listarPorData(Node* raiz) {
    if (raiz == NULL) return;
    listarPorData(raiz->esquerda);
    printf("Tarefa: %s | Data: %d | Prioridade: %s\n",
           raiz->tarefa.descricao,
           raiz->tarefa.data_vencimento,
           raiz->tarefa.prioridade);
    listarPorData(raiz->direita);
}

void filtrarPrioridade(Node* raiz, const char* prioridade) {
    if (raiz == NULL) return;
    filtrarPrioridade(raiz->esquerda, prioridade);
    if (strcmp(raiz->tarefa.prioridade, prioridade) == 0) {
        printf("Tarefa: %s | Data: %d | Prioridade: %s\n",
               raiz->tarefa.descricao,
               raiz->tarefa.data_vencimento,
               raiz->tarefa.prioridade);
    }
    filtrarPrioridade(raiz->direita, prioridade);
}

int obterDataAtual() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year * 10000 + (tm.tm_mon + 1) * 100 + tm.tm_mday;
}

void notificarVencidas(Node* raiz, int dataAtual) {
    if (raiz == NULL) return;
    notificarVencidas(raiz->esquerda, dataAtual);
    if (raiz->tarefa.data_vencimento < dataAtual) {
        printf("TAREFA VENCIDA: %s | Data: %d | Prioridade: %s\n",
               raiz->tarefa.descricao,
               raiz->tarefa.data_vencimento,
               raiz->tarefa.prioridade);
    }
    notificarVencidas(raiz->direita, dataAtual);
}

// Criar tarefa
Tarefa criarTarefa(const char* descricao, int data, const char* prioridade) {
    Tarefa t;
    strncpy(t.descricao, descricao, sizeof(t.descricao));
    t.data_vencimento = data;
    strncpy(t.prioridade, prioridade, sizeof(t.prioridade));
    return t;
}

int main() {
    Node* raiz = NULL;

    raiz = inserir(raiz, criarTarefa("Entregar trabalho de engenharia", 20250410, "alta"));
    raiz = inserir(raiz, criarTarefa("Comprar presente", 20250420, "media"));
    raiz = inserir(raiz, criarTarefa("Pagar contas", 20250415, "baixa"));
    raiz = inserir(raiz, criarTarefa("Estudar para prova", 20250412, "alta"));

    printf("Todas as tarefas em ordem de vencimento:\n");
    listarPorData(raiz);

    printf("\nTarefas com prioridade alta:\n");
    filtrarPrioridade(raiz, "alta");

    int hoje = obterDataAtual();
    printf("\nTarefas vencidas (data atual: %d):\n", hoje);
    notificarVencidas(raiz, hoje);

    return 0;
}
