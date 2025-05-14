#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} No;

No* CriNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo) {
        novo->valor = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
    }
    return novo;
}

No* Insertion(No* raiz, int valor) {
    if(raiz == NULL) {
        return CriNo(valor);
    }

    if(valor < raiz->valor) {
        raiz->esquerda = Insertion(raiz->esquerda, valor);
    } else if(valor > raiz->valor) {
        raiz->direita = Insertion(raiz->direita, valor);
    }

    return raiz;
}

