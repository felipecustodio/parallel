#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define T 4

int main(int argc,char **argv){
    double wtime;
    /*
    Não modifique este trecho de código
    *************************************************************************************
    */

     	int *vetor,i,maior=0,tam;
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
      
    
/*    printf("tam=%d \n", tam);
    fflush(0);
    for(i=0;i<tam;i++) {
        printf("%d\n", vetor[i]); // elementos lidos do vetor
	fflush(0);
    }
*/
    wtime = omp_get_wtime();

    maior=vetor[0];
    #pragma omp parallel for num_threads(T) reduction (max: maior)
    for(i=1;i<tam;i++){
        if(vetor[i]>maior)
            maior=vetor[i];
    }

   /*
    *************************************************************************************
    Não modifique este trecho de código
    */
   
    wtime = omp_get_wtime() - wtime;

    printf("PAR REDUCTION: Tam=%d, maior=%d, Elapsed wall clock time = %f  \n", tam, maior, wtime); //Imprime o vetor ordenado
    free(vetor); //Desaloca o vetor lido
    return 0;
}