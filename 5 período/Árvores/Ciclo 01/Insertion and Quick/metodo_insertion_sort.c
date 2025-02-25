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
    
    for (int i = 1; i < MAX; i++) {
        int chave = lista[i]; 
        int j = i - 1;

        while (j >= 0 && lista[j] > chave) {
            lista[j + 1] = lista[j];
            j = j - 1;
        }
        lista[j + 1] = chave;

        printf("\n\n|");    

        for(int i = 0; i < MAX; i++) {
            printf(" %d |", lista[i]);
        }
    }
    
    return 0;
}