#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#ifdef _WIN32
    #include <windows.h>
#endif

/* FUNÇÃO ADICIONAIS */

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void exibir(int list[], int max) {
	printf("LISTA = ");
	for(int i = 0; i < max; i++) {
		printf("| %d ", list[i]);
	}
	printf("|\n\n");
}

void line() {
	for(int i = 0; i < 25; i++){
		printf("=-");
	}
}

void copy(int list[], int listcopy[], int max) {
	for (int i = 0; i < max; i++) {
		listcopy[i] = list[i];
	}
}

void result(char *text, int max, float temp, int comp, int movi) {
	line();
	printf("\n\n%s com %d dados\n", text, max);
	printf("TEMPO        = %.3f\n", temp);
	printf("COMPARACAO   = %d\n", comp);
	printf("MOVIMENTACAO = %d\n\n", movi);
}

void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* FUNÇÃO BUBBLE-SORT */

int Bubble(int list[], int max, int choice) {
	int tro, com = 0, mov = 0;
	char type[25];

	clock_t start = clock();
	do {
		tro = 0;
		for(int i = 0; i < max-1; i++) {
			com++;
			if (list[i] > list[i+1] && choice == 1) {
				troca(&list[i], &list[i+1]);
				mov++;
				tro = 1;
				snprintf(type, sizeof(type), "Crescente");
			}
			if (list[i] < list[i+1] && choice == 0) {
				troca(&list[i], &list[i+1]);
				mov++;
				tro = 1;
				snprintf(type, sizeof(type), "Decrescente");
			}
		}
	} while (tro);
	clock_t end = clock();

	double tim = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    char text[50];
	snprintf(text, sizeof(text), "Bubble %s", type);

	result(text, max, tim, com, mov);

	return 0;
}

/* FUNÇÃO SELECTION-SORT */

int SelectionCre(int list[], int max) {
	int pos, tem, com = 0, mov = 0;

	clock_t start = clock();

    for(int i = 0; i < max - 1; i++) {
        pos = i;

        for(int j = i + 1; j < max; j++) {
            com++;
            if (list[j] < list[pos]) {
                pos = j;
            }
        }

        if (pos != i) {
            tem = list[i];
            list[i] = list[pos];
            list[pos] = tem;
            mov++;
        }
    }

	clock_t end = clock();

	double tim = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    char text[50] = "Selection Cresente";

	result(text, max, tim, com, mov);

	return 0;
}

int SelectionDec(int list[], int max) {
	int pos, tem, com = 0, mov = 0;

	clock_t start = clock();

    for(int i = 0; i < max - 1; i++) {
        pos = i;

        for(int j = i + 1; j < max; j++) {
            com++;
            if (list[j] > list[pos]) {
                pos = j;
            }
        }

        if (pos != i) {
            tem = list[i];
            list[i] = list[pos];
            list[pos] = tem;
            mov++;
        }
    }

	clock_t end = clock();

	double tim = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    char text[50] = "Selection Decresente";

	result(text, max, tim, com, mov);
	
	return 0;
}

/* FUNÇÃO INSERTION-SORT */

int InsertionCre(int list[], int max) {
	int cha, com = 0, mov = 0;

	clock_t start = clock();
	
	for (int i = 1; i < max; i++) {
		cha = list[i];
		int j = i - 1;

		com++;
		while (j >= 0 && list[j] > cha) {
			list[j + 1] = list[j];
			j--;
			mov++;
		}
		list[j + 1] = cha;
	}

	clock_t end = clock();

	double tim = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    char text[50] = "Insertion Cresente";

	result(text, max, tim, com, mov);

	return 0;
}

int InsertionDec(int list[], int max) {
	int cha, com = 0, mov = 0;

	clock_t start = clock();
	
	for (int i = i; i < max; i++) {
		cha = list[i];
		int j = i - 1;

		com++;
		while (j >= 0 && list[j] < cha) {
			list[j + 1] = list[j];
			j--;
			mov++;
		}
		list[j + 1] = cha;
	}

	clock_t end = clock();

	double tim = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    char text[50] = "Insertion Decresente";

	result(text, max, tim, com, mov);
	
	return 0;
}

/* FUNÇÃO QUICK-SORT */

int particionar(int vetor[], int baixo, int alto, int choice, int *com, int *mov) {
    int pivo = vetor[alto];
    int i = baixo - 1;

    for (int j = baixo; j < alto; j++) {
		(*com)++;
        if (vetor[j] <= pivo && choice == 1) {
            i++;
            troca(&vetor[i], &vetor[j]);
			(*mov)++;
        }
        if (vetor[j] >= pivo && choice == 0) {
            i++;
            troca(&vetor[i], &vetor[j]);
			(*mov)++;
        }
    }
    troca(&vetor[i + 1], &vetor[alto]);
	(*mov)++;
    return i + 1;
}

void quickSort(int vetor[], int baixo, int alto, int choice, int *com, int *mov) {
    if (baixo < alto) {
        int pi = particionar(vetor, baixo, alto, choice, com, mov);
        quickSort(vetor, baixo, pi - 1, choice, com, mov);
        quickSort(vetor, pi + 1, alto, choice, com, mov);
    }
}

int Quick(int list[], int max, int choice) {
	int com = 0, mov = 0;
	char type[25];

	clock_t start = clock();

	if (choice == 1) {
		snprintf(type, sizeof(type), "Crescente");
		quickSort(list, 0, max - 1, 1, &com, &mov);
	} else if (choice == 0) {
		snprintf(type, sizeof(type), "Decrescente");
		quickSort(list, 0, max - 1, 0, &com, &mov);
	} else {
		printf("\n\tERROR\n\n");
		return 0;
	}

	clock_t end = clock();

	double tim = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    char text[50];
	snprintf(text, sizeof(text), "Quick %s", type);

	result(text, max, tim, com, mov);
	
	return 0;
}

/* FUNÇÃO PRINCIPAL */

int main() {
    clearScreen();
	int choice;
	printf("quantos dados tem na listas: ");
	scanf("%d", &choice);

	int list[choice], listcopy[choice];

	srand(time(NULL));

	for(int i = 0; i < choice; i++) {
		list[i] = (rand() % 99) + 1;
	}

	exibir(list, choice);
    //--------------------------------------------------
	copy(list, listcopy, choice);
	Bubble(listcopy, choice, 1);
	copy(list, listcopy, choice);
	Bubble(listcopy, choice, 0);
    //--------------------------------------------------
	copy(list, listcopy, choice);
	SelectionCre(listcopy, choice);
	copy(list, listcopy, choice);
	SelectionDec(listcopy, choice);
    //--------------------------------------------------
	copy(list, listcopy, choice);
	InsertionCre(listcopy, choice);
	copy(list, listcopy, choice);
	InsertionDec(listcopy, choice);
    //--------------------------------------------------
	copy(list, listcopy, choice);
	Quick(listcopy, choice, 1);
	copy(list, listcopy, choice);
	Quick(listcopy, choice, 0);
}