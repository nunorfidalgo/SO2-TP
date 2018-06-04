#include <windows.h>
#include "utils.h"
#include <time.h>

// Inicializa o gerador de numeros aleatorios
void init_rand() {
	srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max) {
	return min + rand() % (max - min + 1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01() {
	return ((float)rand()) / RAND_MAX;
}