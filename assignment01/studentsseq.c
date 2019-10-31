/*
   Este programa calcula as seguintes estatisticas
   das notas dos alunos nas escolas das diferentes
   cidades do Brasil:
   Menor, Maior, Media, Mediana e Desvio Padrao (DP)
   */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

/*
   Entrada do programa:
   R = Numero de regioes distintas.
   C = Numero de cidades distintas.
   A = Numero de alunos por cidade.
   SEED = semente usada para gerar numeros aleatorios.
   */
int R, C, A, SEED;

/*
Dados:
alunos  = Notas de cada aluno k.
cidades = Notas de cada aluno k de cada cidade j.
regioes = Notas de cada aluno k de cada cidade j
de cada regiao i.

*/
int *alunos;
int **cidades;
int ***regioes;

/*
   Estatisticas das cidades referentes
   a cada cidade j de cada regiao i:
   */
int **menor;
int **maior;
double **mediana;
double **media;
double **DP;

/*
   Estatisticas das regioes referentes
   a cada regiao i:
   */
int *menor_regiao;
int *maior_regiao;
double *mediana_regiao;
double *media_regiao;
double *DP_regiao;

/*
   Estatisticas de todas as regioes
   */
int menor_brasil;
int maior_brasil;
double mediana_brasil;
double media_brasil;
double DP_brasil;

/*
   Indice da melhor regiao e da melhor
   cidade e sua respectiva regiao:
   */
int melhor_regiao;
int melhor_cidade_regiao;
int melhor_cidade;


void debug() {


}


int comparador(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void ordena() {
    int i, j;
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            qsort(regioes[i][j], A, sizeof(int), comparador);
        }
    }
}


void calcula_menor() {

}

void calcula_maior() {

}

void calcula_media() {

}

void calcula_mediana() {

}

void calcula_desvio_padrao() {

}

int main(int argc, char *argv[]) {
    /*
    Variaveis para o calculo do tempo de execucao
    e indices dos loops.
    */
    double start_time, time;
    int i, j, k;

    // Leitura dos dados
    scanf("%d %d %d %d", &R, &C, &A, &SEED);

    // Definicao da semente aleatoria
    srand(SEED);

// Alocacao de memoria:
    // Geracao das matrizes
#ifndef DEBUG
    regioes = (int ***) malloc(sizeof(int **) * R);
    for (i = 0; i < R; i++) {
        cidades = (int **) malloc(sizeof(int *) * C);
        for (j = 0; j < C; j++) {
            alunos = (int *) malloc(sizeof(int) * A);
            for (k = 0; k < A; k++) {
                alunos[k] = rand() % 101;
            }
            cidades[j] = alunos;
        }
        regioes[i] = cidades;
    }
#else
    debug();
#endif
    // Alocacao de memoria para os resultados:
    // Cidades
    menor = (int **) malloc(sizeof(int *) * R);
    maior = (int **) malloc(sizeof(int *) * R);
    mediana = (double **) malloc(sizeof(double *) * R);
    media = (double **) malloc(sizeof(double *) * R);
    DP = (double **) malloc(sizeof(double *) * R);
    for (i = 0; i < R; i++) {
        menor[i] = (int *) malloc(sizeof(int) * C);
        maior[i] = (int *) malloc(sizeof(int) * C);
        mediana[i] = (double *) malloc(sizeof(double) * C);
        media[i] = (double *) malloc(sizeof(double) * C);
        DP[i] = (double *) malloc(sizeof(double) * C);
    }

    // Regioes
    menor_regiao = (int *) malloc(sizeof(int) * R);
    maior_regiao = (int *) malloc(sizeof(int) * R);
    mediana_regiao = (double *) malloc(sizeof(double) * R);
    media_regiao = (double *) malloc(sizeof(double) * R);
    DP_regiao = (double *) malloc(sizeof(double) * R);

// Calculo das estatisticas

    start_time = omp_get_wtime();

    ordena();

    time = omp_get_wtime() - start_time;

    // Impressao dos resultados:
    // Cidades
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            printf("Reg %d - Cid %d: "
                    "menor: %d, "
                    "maior: %d, "
                    "mediana: %.2lf, "
                    "media: %.2lf e "
                    "DP: %.2lf\n",
                    i, j,
                    menor[i][j],
                    maior[i][j],
                    mediana[i][j],
                    media[i][j],
                    DP[i][j]);
        }
        printf("\n");
    }

    // Regioes
    for (i = 0; i < R; i++) {
        printf("Reg %d: "
                "menor: %d, "
                "maior: %d, "
                "mediana: %.2lf, "
                "media: %.2lf e "
                "DP: %.2lf\n",
                i,
                menor_regiao[i],
                maior_regiao[i],
                mediana_regiao[i],
                media_regiao[i],
                DP_regiao[i]);
    }
    printf("\n");

    // Brasil
    printf("Brasil: "
            "menor: %d, "
            "maior: %d, "
            "mediana: %.2lf, "
            "media: %.2lf e "
            "DP: %.2lf\n\n",
            menor_brasil,
            maior_brasil,
            mediana_brasil,
            media_brasil,
            DP_brasil);

    // Melhores
    printf("Melhor regiao: Regiao %d\n"
            "Melhor cidade: Regiao %d, "
            "Cidade %d\n",
            melhor_regiao,
            melhor_cidade_regiao,
            melhor_cidade);

    // Tempo de execucao
    printf("Tempo de execucao: %g\n", time);

    // Desalocacao de memoria
    for (i = 0; i < R; i++) {
        free(menor[i]);
        free(maior[i]);
        free(mediana[i]);
        free(media[i]);
        free(DP[i]);
        for (j = 0; j < C; j++) {
            free(regioes[i][j]);
        }
        free(regioes[i]);
    }
    free(regioes);
    free(menor);
    free(maior);
    free(mediana);
    free(media);
    free(DP);
    free(menor_regiao);
    free(maior_regiao);
    free(mediana_regiao);
    free(media_regiao);
    free(DP_regiao);

    return 0;
}
