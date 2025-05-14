#include <stdio.h>
#include <stdlib.h>

// Definindo o nó da árvore
typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
} No;

// Função para criar um novo nó
No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo) {
        novo->valor = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
    }
    return novo;
}

// Função para inserir um valor na árvore
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

// Função para buscar um valor na árvore
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

// Função para percorrer a árvore em ordem
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

// Função para imprimir a árvore espelhada visualmente
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

// Função para liberar memória da árvore
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

// Programa principal
int main() {
    No* raiz = NULL;
    int opcao, valor;
    No* resultadoBusca;

    do {
        printf("\n--- Menu ---\n");
        printf("1. Inserir valor\n");
        printf("2. Buscar valor\n");
        printf("3. Mostrar em ordem\n");
        printf("4. Sair\n");
        printf("5. Imprimir estrutura da arvore\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor para inserir: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                break;
            case 2:
                printf("Digite o valor para buscar: ");
                scanf("%d", &valor);
                resultadoBusca = buscar(raiz, valor);
                if (resultadoBusca != NULL) {
                    printf("Valor %d encontrado na arvore.\n", resultadoBusca->valor);
                } else {
                    printf("Valor %d nao encontrado.\n", valor);
                }
                break;
            case 3:
                printf("Arvore em ordem: ");
                emOrdem(raiz);
                printf("\n");
                break;
            case 4:
                printf("Saindo...\n");
                break;
            case 5:
                printf("Visual da arvore:\n\n");
                imprimirArvore(raiz, 0);
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    liberarArvore(raiz);
    return 0;
}
