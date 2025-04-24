#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Filme {
    char titulo[100];
    char genero[50];
    int classificacao;
    float pontuacao;
} Filme;

typedef struct Node {
    Filme filme;
    struct Node* esquerda;
    struct Node* direita;
} Node;

// Criação de um novo nó
Node* criarNo(Filme filme) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->filme = filme;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

// Inserir na ABB com base na pontuação média
Node* inserir(Node* raiz, Filme filme) {
    if (raiz == NULL) {
        return criarNo(filme);
    }
    if (filme.pontuacao < raiz->filme.pontuacao)
        raiz->esquerda = inserir(raiz->esquerda, filme);
    else
        raiz->direita = inserir(raiz->direita, filme);
    return raiz;
}

// Buscar filmes por gênero
void buscarPorGenero(Node* raiz, const char* genero) {
    if (raiz == NULL) return;
    buscarPorGenero(raiz->esquerda, genero);
    if (strcmp(raiz->filme.genero, genero) == 0) {
        printf("Titulo: %s | Genero: %s | Classificacao: %d | Pontuacao: %.1f\n",
               raiz->filme.titulo, raiz->filme.genero, raiz->filme.classificacao, raiz->filme.pontuacao);
    }
    buscarPorGenero(raiz->direita, genero);
}

// Atualizar a pontuação média de um filme pelo título
int atualizarPontuacao(Node* raiz, const char* titulo, float novaPontuacao) {
    if (raiz == NULL) return 0;

    if (strcmp(raiz->filme.titulo, titulo) == 0) {
        raiz->filme.pontuacao = novaPontuacao;
        return 1;
    }
    return atualizarPontuacao(raiz->esquerda, titulo, novaPontuacao) ||
           atualizarPontuacao(raiz->direita, titulo, novaPontuacao);
}

// Armazenar os top 5 filmes
void armazenarTopFilmes(Node* raiz, Filme top[], int* count) {
    if (raiz == NULL || *count >= 5) return;
    armazenarTopFilmes(raiz->direita, top, count);
    if (*count < 5) {
        top[*count] = raiz->filme;
        (*count)++;
        armazenarTopFilmes(raiz->esquerda, top, count);
    }
}

// Mostrar top 5 filmes
void mostrarTop5(Node* raiz) {
    Filme top[5];
    int count = 0;
    armazenarTopFilmes(raiz, top, &count);
    printf("\nTop %d filmes com maior pontuacao:\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d. %s (%.1f)\n", i + 1, top[i].titulo, top[i].pontuacao);
    }
}

// Função auxiliar para criar filmes
Filme criarFilme(const char* titulo, const char* genero, int classificacao, float pontuacao) {
    Filme f;
    strncpy(f.titulo, titulo, sizeof(f.titulo));
    strncpy(f.genero, genero, sizeof(f.genero));
    f.classificacao = classificacao;
    f.pontuacao = pontuacao;
    return f;
}

int main() {
    Node* raiz = NULL;

    // Inserção de alguns filmes
    raiz = inserir(raiz, criarFilme("Interestelar", "Ficcao", 12, 9.0));
    raiz = inserir(raiz, criarFilme("Matrix", "Ficcao", 14, 8.7));
    raiz = inserir(raiz, criarFilme("O Poderoso Chefao", "Drama", 18, 9.2));
    raiz = inserir(raiz, criarFilme("Shrek", "Animacao", 0, 8.4));
    raiz = inserir(raiz, criarFilme("Toy Story", "Animacao", 0, 8.3));
    raiz = inserir(raiz, criarFilme("Corra!", "Terror", 16, 7.9));
    raiz = inserir(raiz, criarFilme("A Origem", "Ficcao", 14, 8.8));

    printf("\nFilmes do genero 'Ficcao':\n");
    buscarPorGenero(raiz, "Ficcao");

    printf("\nAtualizando pontuacao de 'Shrek' para 9.5...\n");
    if (atualizarPontuacao(raiz, "Shrek", 9.5)) {
        printf("Pontuacao atualizada com sucesso!\n");
    } else {
        printf("Filme nao encontrado.\n");
    }

    mostrarTop5(raiz);

    return 0;
}