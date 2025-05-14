#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} No;

No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo) {
        novo->valor = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
    }
    return novo;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return criarNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    }
    return raiz;
}

No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }
    if (valor < raiz->valor) {
        return buscar(raiz->esquerda, valor);
    } else {
        return buscar(raiz->direita, valor);
    }
}

void preOrdem(No* raiz) { 
    if (raiz != NULL) { 
        printf("%d ", raiz->valor); 
        preOrdem(raiz->esquerda); 
        preOrdem(raiz->direita); 
    } 
}

void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

void posOrdem(No* raiz) { 
    if (raiz != NULL) { 
        posOrdem(raiz->esquerda); 
        posOrdem(raiz->direita); 
        printf("%d ", raiz->valor); 
    } 
}

void imprimirArvore(No* raiz, int espaco) {
    if (raiz == NULL)
        return;

    int espacoEntreNiveis = 5;
    espaco += espacoEntreNiveis;

    imprimirArvore(raiz->direita, espaco);

    for (int i = espacoEntreNiveis; i < espaco; i++)
        printf(" ");
    printf("%d\n", raiz->valor);

    imprimirArvore(raiz->esquerda, espaco);
}

void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int main() {
    No* raiz = NULL;
    int opcao, valor;
    No* resultadoBusca;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 1);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 22 );
    
    resultadoBusca = buscar(raiz, 10);
    if (resultadoBusca != NULL) {
        printf("Valor %d encontrado na arvore.\n\n", resultadoBusca->valor);
    } else {
        printf("Valor %d nao encontrado.\n\n", valor);
    }
    
    resultadoBusca = buscar(raiz, 2);
    if (resultadoBusca != NULL) {
        printf("Valor %d encontrado na arvore.\n\n", resultadoBusca->valor);
    } else {
        printf("Valor %d nao encontrado.\n\n", valor);
    }

    printf("Arvore pre ordem: ");
    preOrdem(raiz);
    printf("\n\n");
    
    printf("Arvore em ordem: ");
    emOrdem(raiz);
    printf("\n\n");
    
    printf("Arvore pos ordem: ");
    posOrdem(raiz);
    printf("\n\n");

    
    printf("Visual da arvore:\n\n");
    imprimirArvore(raiz, 0);

    liberarArvore(raiz);

    return 0;
}
