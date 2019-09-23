// Encontra o valor minimo em um vetor de inteiros de tamanho N
// algoritmo baseado em Grama et al. (2003)
// GRAMA,A.; KUMAR, U.; GUPTA,A.; KARYPIS, G. Introduction to Parallel Computing, 
//  2nd Edition, 2003, ISBN: 0201648652, seção 3.2.1, Algoritmo 3.1.
//
// para compilar: gcc minimo_seq.c -o minimo_seq
// para executar: minimo_seq
//

#include <stdlib.h>
#include <stdio.h>

#define N 450000000		// numero de iteracoes

int A[N], min;


void main(void) {
	int i;
	
	for (i = 0; i < N; i++) {
	    A[i] = (N - 1) - i;
//	    A[i] = rand() % 10000;
	}


	min = A[0]; 
	for (i = 1; i< N; i++) 
	    if (A[i] < min) 
		min = A[i]; 
	
	printf("min = %d, N = %d SEQ \n", min, N);

	fflush(0);
	return;
} // fim main()
