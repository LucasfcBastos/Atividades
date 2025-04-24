#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contato {
    char nome[100];
    char telefone[20];
    char email[100];
} Contato;

typedef struct Node {
    Contato contato;
    struct Node* esquerda;
    struct Node* direita;
} Node;

// Criar novo no
Node* criarNo(Contato c) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->contato = c;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Inserir contato na ABB
Node* inserir(Node* raiz, Contato c) {
    if (raiz == NULL) return criarNo(c);
    if (strcmp(c.nome, raiz->contato.nome) < 0)
        raiz->esquerda = inserir(raiz->esquerda, c);
    else if (strcmp(c.nome, raiz->contato.nome) > 0)
        raiz->direita = inserir(raiz->direita, c);
    return raiz;
}

// Buscar contato por nome
Node* buscar(Node* raiz, const char* nome) {
    if (raiz == NULL || strcmp(raiz->contato.nome, nome) == 0)
        return raiz;
    if (strcmp(nome, raiz->contato.nome) < 0)
        return buscar(raiz->esquerda, nome);
    else
        return buscar(raiz->direita, nome);
}

// Atualizar contato
int atualizar(Node* raiz, const char* nome, const char* novoTelefone, const char* novoEmail) {
    Node* encontrado = buscar(raiz, nome);
    if (encontrado != NULL) {
        strcpy(encontrado->contato.telefone, novoTelefone);
        strcpy(encontrado->contato.email, novoEmail);
        return 1;
    }
    return 0;
}

// Minimo da subarvore
Node* minimo(Node* raiz) {
    while (raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

// Remover contato
Node* remover(Node* raiz, const char* nome) {
    if (raiz == NULL) return NULL;
    if (strcmp(nome, raiz->contato.nome) < 0)
        raiz->esquerda = remover(raiz->esquerda, nome);
    else if (strcmp(nome, raiz->contato.nome) > 0)
        raiz->direita = remover(raiz->direita, nome);
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
        raiz->contato = temp->contato;
        raiz->direita = remover(raiz->direita, temp->contato.nome);
    }
    return raiz;
}

// Listar contatos em ordem alfabetica
void listarContatos(Node* raiz) {
    if (raiz == NULL) return;
    listarContatos(raiz->esquerda);
    printf("Nome: %s | Telefone: %s | Email: %s\n",
           raiz->contato.nome, raiz->contato.telefone, raiz->contato.email);
    listarContatos(raiz->direita);
}

// Autocompletar nomes
void autocompletar(Node* raiz, const char* prefixo) {
    if (raiz == NULL) return;
    autocompletar(raiz->esquerda, prefixo);
    if (strncmp(raiz->contato.nome, prefixo, strlen(prefixo)) == 0) {
        printf("Nome: %s | Telefone: %s | Email: %s\n",
               raiz->contato.nome, raiz->contato.telefone, raiz->contato.email);
    }
    autocompletar(raiz->direita, prefixo);
}

// Criar contato
Contato criarContato(const char* nome, const char* telefone, const char* email) {
    Contato c;
    strncpy(c.nome, nome, sizeof(c.nome));
    strncpy(c.telefone, telefone, sizeof(c.telefone));
    strncpy(c.email, email, sizeof(c.email));
    return c;
}

// Main
int main() {
    Node* agenda = NULL;

    // Inserir contatos
    agenda = inserir(agenda, criarContato("Carlos Alberto", "9999-0001", "carlos@email.com"));
    agenda = inserir(agenda, criarContato("Ana Paula", "9999-0002", "ana@email.com"));
    agenda = inserir(agenda, criarContato("Bruno Silva", "9999-0003", "bruno@email.com"));
    agenda = inserir(agenda, criarContato("Amanda Costa", "9999-0004", "amanda@email.com"));

    printf("\nTodos os contatos:\n");
    listarContatos(agenda);

    printf("\nBusca por nome completo (Bruno Silva):\n");
    Node* b = buscar(agenda, "Bruno Silva");
    if (b) {
        printf("Encontrado: %s | %s | %s\n", b->contato.nome, b->contato.telefone, b->contato.email);
    } else {
        printf("Contato nao encontrado.\n");
    }

    printf("\nAtualizando telefone de Ana Paula...\n");
    atualizar(agenda, "Ana Paula", "8888-0000", "ana_novo@email.com");

    printf("\nContatos comecando com 'A':\n");
    autocompletar(agenda, "A");

    printf("\nRemovendo contato: Carlos Alberto\n");
    agenda = remover(agenda, "Carlos Alberto");

    printf("\nContatos apos remocao:\n");
    listarContatos(agenda);

    return 0;
}