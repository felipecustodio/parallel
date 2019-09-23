#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

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
    

    wtime = omp_get_wtime();

    maior=vetor[0];
    for(i=1;i<tam;i++){
        if(vetor[i]>maior)
            maior=vetor[i];
    }

    wtime = omp_get_wtime() - wtime;

   /*
    *************************************************************************************
    Não modifique este trecho de código
    */
   
    printf("SEQ: Tam=%d, maior=%d Elapsed wall clock time = %f \n", tam, maior, wtime); //Imprime o vetor ordenado
    free(vetor); //Desaloca o vetor lido
    
    return 0;
    
}