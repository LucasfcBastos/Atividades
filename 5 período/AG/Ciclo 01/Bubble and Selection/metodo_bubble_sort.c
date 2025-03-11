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
    
    int trocou;
    
    do {

        trocou = 0;
        for(int i = 0; i < MAX - 1; i++) {
            if (lista[i] > lista[i + 1]) {
                int temp = lista[i];
                lista[i] = lista[i + 1];
                lista[i + 1] = temp;
                trocou = 1;
            }
        }

        printf("\n\n|");
    
        for(int i = 0; i < MAX; i++) {
            printf(" %d |", lista[i]);
        }

    } while (trocou);
    
    return 0;
}