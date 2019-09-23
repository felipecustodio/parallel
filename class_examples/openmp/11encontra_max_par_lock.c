#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define T 8

int main(int argc,char **argv){
    double wtime;
    
    /*
    Não modifique este trecho de código
    *************************************************************************************
    */
    	int *vetor,i,maior, localmaior, tam, num_threads;
//	fscanf(stdin, "%d\n", &tam); //Lê a dimensão do vetor
	tam = 90000000;
	vetor=(int*)malloc(tam*sizeof(int)); //Aloca o vetor da dimensão lida
//    for(i=0;i<tam;i++)
//        fscanf(stdin, "%d\n", &(vetor[i])); //Lê os elementos do vetor
//    
    /************************************************************************************
  Modifique a partir daqui
    */

      // iniciando vetor com nrs aleatorios e fixando o maior valor para validacao
      for(i=0;i<tam;i++)
        vetor[i] = rand() % 10000;
	vetor[tam/2] = 10001;
      
      
	omp_lock_t mylock;
	omp_init_lock(&mylock);

    wtime = omp_get_wtime();

    localmaior = maior = -1;
    #pragma omp parallel num_threads(T) shared (maior) private(localmaior)
    {
		int my_id, my_range, my_first_i, my_last_i;
		
		// determina o nr da thread
		my_id = omp_get_thread_num();  //

		// determina o nr de threads
		num_threads = omp_get_num_threads();

		my_range = tam/num_threads;
		
		my_first_i = my_range * my_id;
		
		if (my_id < num_threads-1)
			my_last_i = my_first_i + my_range; // na verdade eh o primeiro do proximo range
		else
			my_last_i = tam; // a ultima thread fica com o resto, caso divisao N/num_threads não for exata
		
        for(i = my_first_i; i < my_last_i; i++){
            if(vetor[i] > localmaior)
                localmaior=vetor[i];
        }
		
		omp_set_lock(&mylock);
		if (localmaior > maior)
			maior = localmaior;
		omp_unset_lock(&mylock);

	}

   /*
    *************************************************************************************
    Não modifique este trecho de código
    */
    wtime = omp_get_wtime() - wtime;

    printf("PAR LOCK: Tam=%d, Num_Threads=%d, maior=%d, Elapsed wall clock time = %f  \n", tam, num_threads, maior, wtime); //Imprime o vetor ordenado
    free(vetor); //Desaloca o vetor lido
    return 0;
}