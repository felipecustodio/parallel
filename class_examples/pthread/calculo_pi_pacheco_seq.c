// Calcula uma aproximacao do numero pi (3,14159 26535 89793 23846 26433 83279)
// algoritmo baseado em Pacheco (2011), pp 163, Seção 4.4 e Program 4.3.
//
// para compilar: gcc calculo_pi_pacheco_seq.c -o calculo_pi_pacheco_seq
// para executar: calculo_pi_pacheco_seq
//

#include <stdlib.h>
#include <stdio.h>

#define N 1000000000		// numero de iteracoes

double sum = 0.0;


int main(void) {
	double factor = 1.0;
	long long i;
	
	for (i = 0; i < N; i++, factor = -factor) {
		sum = sum + (factor / (2 * i + 1));
	}

	sum = 4 * sum;
	printf("pi = %.15f, N = %d  SEQ \n", sum, N);

	fflush(0);
	return(0);
} // fim main()
