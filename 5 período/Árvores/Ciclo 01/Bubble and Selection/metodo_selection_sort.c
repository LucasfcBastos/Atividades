#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX 5

int main() {
    int lista[MAX], numb;
    
    for(int i = 0; i < MAX; i++) {
        printf("Escola um numero para casa %d: \n", i);
        scanf("%d", &numb);
        lista[i] = numb;
    }

    printf("\n\n|");

    for(int i = 0; i < MAX; i++) {
        printf(" %d |", lista[i]);
    }

    int posicao, temp;
    
    for(int i = 0; i < MAX - 1; i++) {
        posicao = i;
        
        for(int j = i + 1; j < MAX; j++) {
            if (lista[j] < lista[posicao]) {
                posicao = j;
            }
        }

        if (posicao != i) {
            temp = lista[i];
            lista[i] = lista[posicao];
            lista[posicao] = temp;
        }

        printf("\n\n|");
    
        for(int i = 0; i < MAX; i++) {
            printf(" %d |", lista[i]);
        }

    }

    return 0;
}
