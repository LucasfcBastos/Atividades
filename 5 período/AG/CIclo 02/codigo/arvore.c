#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

// Inserção na árvore binária de busca
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        No* novo = (No*)malloc(sizeof(No));
        novo->valor = valor;
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    } else {
        raiz->dir = inserir(raiz->dir, valor);
    }

    return raiz;
}

// Busca na árvore
No* busca(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    }

    if (valor < raiz->valor) {
        return busca(raiz->esq, valor);
    } else {
        return busca(raiz->dir, valor);
    }
}

// Encontra o menor valor da subárvore
No* minimo(No* raiz) {
    while (raiz->esq != NULL) {
        raiz = raiz->esq;
    }
    return raiz;
}

// Remoção de um nó da árvore
No* remover(No* raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        // Sem filhos
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }

        // Um filho
        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // Dois filhos
        No* sucessor = minimo(raiz->dir);
        raiz->valor = sucessor->valor;
        raiz->dir = remover(raiz->dir, sucessor->valor);
    }

    return raiz;
}

// Impressão in-order
void imprimirEmOrdem(No* raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        imprimirEmOrdem(raiz->dir);
    }
}

// Libera todos os nós da árvore
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

void menu() {
    printf("\n==============================\n");
    printf("1 - Adicionar um novo número\n");
    printf("2 - Buscar um número\n");
    printf("3 - Excluir um número\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

// Função principal
int main() {
    int opc, numb;
    No* raiz = NULL;
    
    do {
        menu();
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                printf("Digite o número: ");
                scanf("%d", &numb);
                raiz = inserir(raiz, numb);
                printf("Árvore em ordem: ");
                imprimirEmOrdem(raiz);
                printf("\n");
                break;
            case 2:
                printf("Digite o número para buscar: ");
                scanf("%d", &numb);
                if (busca(raiz, numb) != NULL) {
                    printf("Número %d encontrado na árvore.\n", numb);
                } else {
                    printf("Número %d NÃO encontrado.\n", numb);
                }
                break;
            case 3:
                printf("Digite o número para excluir: ");
                scanf("%d", &numb);
                raiz = remover(raiz, numb);
                printf("Árvore em ordem: ");
                imprimirEmOrdem(raiz);
                printf("\n");
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

    } while (opc != 0);

    // Libera memória alocada
    liberarArvore(raiz);
    return 0;
}