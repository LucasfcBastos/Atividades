#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    int id;
    char nome[100];
    int quantidade;
    float preco;
} Produto;

typedef struct Node {
    Produto produto;
    struct Node* esquerda;
    struct Node* direita;
} Node;

// Criar novo no
Node* criarNo(Produto produto) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->produto = produto;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Inserir produto na ABB
Node* inserir(Node* raiz, Produto produto) {
    if (raiz == NULL)
        return criarNo(produto);
    if (produto.id < raiz->produto.id)
        raiz->esquerda = inserir(raiz->esquerda, produto);
    else if (produto.id > raiz->produto.id)
        raiz->direita = inserir(raiz->direita, produto);
    return raiz;
}

// Buscar produto por ID
Node* buscar(Node* raiz, int id) {
    if (raiz == NULL || raiz->produto.id == id)
        return raiz;
    if (id < raiz->produto.id)
        return buscar(raiz->esquerda, id);
    else
        return buscar(raiz->direita, id);
}

// Atualizar quantidade apos venda
void venderProduto(Node* raiz, int id, int quantidadeVendida) {
    Node* produto = buscar(raiz, id);
    if (produto != NULL) {
        if (produto->produto.quantidade >= quantidadeVendida) {
            produto->produto.quantidade -= quantidadeVendida;
            printf("Venda realizada. Estoque atual: %d\n", produto->produto.quantidade);
        } else {
            printf("Estoque insuficiente.\n");
        }
    } else {
        printf("Produto nao encontrado.\n");
    }
}

// Encontrar o menor valor da subarvore
Node* minimo(Node* raiz) {
    while (raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

// Remover produto da ABB
Node* remover(Node* raiz, int id) {
    if (raiz == NULL)
        return NULL;
    if (id < raiz->produto.id)
        raiz->esquerda = remover(raiz->esquerda, id);
    else if (id > raiz->produto.id)
        raiz->direita = remover(raiz->direita, id);
    else {
        if (raiz->esquerda == NULL) {
            Node* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Node* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        Node* temp = minimo(raiz->direita);
        raiz->produto = temp->produto;
        raiz->direita = remover(raiz->direita, temp->produto.id);
    }
    return raiz;
}

// Listar produtos com estoque abaixo do limite
void listarBaixoEstoque(Node* raiz, int limite) {
    if (raiz == NULL) return;
    listarBaixoEstoque(raiz->esquerda, limite);
    if (raiz->produto.quantidade < limite) {
        printf("ID: %d | Nome: %s | Quantidade: %d | Preco: %.2f\n",
               raiz->produto.id, raiz->produto.nome, raiz->produto.quantidade, raiz->produto.preco);
    }
    listarBaixoEstoque(raiz->direita, limite);
}

// Buscar produtos dentro de uma faixa de preco
void buscarPorFaixaPreco(Node* raiz, float min, float max) {
    if (raiz == NULL) return;
    buscarPorFaixaPreco(raiz->esquerda, min, max);
    if (raiz->produto.preco >= min && raiz->produto.preco <= max) {
        printf("ID: %d | Nome: %s | Quantidade: %d | Preco: %.2f\n",
               raiz->produto.id, raiz->produto.nome, raiz->produto.quantidade, raiz->produto.preco);
    }
    buscarPorFaixaPreco(raiz->direita, min, max);
}

// Criar produto
Produto criarProduto(int id, const char* nome, int quantidade, float preco) {
    Produto p;
    p.id = id;
    strncpy(p.nome, nome, sizeof(p.nome));
    p.quantidade = quantidade;
    p.preco = preco;
    return p;
}

// Main
int main() {
    Node* estoque = NULL;

    // Inserindo produtos
    estoque = inserir(estoque, criarProduto(101, "Mouse USB", 30, 49.99));
    estoque = inserir(estoque, criarProduto(203, "Teclado Mecanico", 15, 199.90));
    estoque = inserir(estoque, criarProduto(150, "Monitor LED", 8, 749.00));
    estoque = inserir(estoque, criarProduto(120, "Headset Gamer", 5, 149.90));
    estoque = inserir(estoque, criarProduto(180, "Webcam HD", 2, 89.00));

    printf("\nProdutos com estoque abaixo de 10:\n");
    listarBaixoEstoque(estoque, 10);

    printf("\nProdutos com preco entre 80.00 e 200.00:\n");
    buscarPorFaixaPreco(estoque, 80.00, 200.00);

    printf("\nRealizando venda de 3 unidades do produto ID 120:\n");
    venderProduto(estoque, 120, 3);

    printf("\nRemovendo produto com ID 150:\n");
    estoque = remover(estoque, 150);

    printf("\nProdutos com estoque abaixo de 10 apos remocao:\n");
    listarBaixoEstoque(estoque, 10);

    return 0;
}