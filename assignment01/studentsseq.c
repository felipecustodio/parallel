// Rodar com a flag -D DEBUG para ativar o modo debug
//#define DEBUG
/*
    Este programa calcula as seguintes estatisticas
    das notas dos alunos nas escolas das diferentes
    cidades do Brasil:
    Menor, Maior, Media, Mediana e Desvio Padrao (DP)
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

#define NOTA_MAXIMA 101

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
    Vetores de contagem de notas
    para o Counting Sort e cálculos
    requisitados.
*/
int ***contagem_cidades;
int **contagem_regioes;
int *contagem_pais;

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
    int i, j;
    R = 3;
    C = 4;
    A = 6;
    SEED = 7;
    regioes = (int ***) malloc(sizeof(int **) * R);
    for (i = 0; i < R; i++) {
        cidades = (int **) malloc(sizeof(int *) * C);
        for (j = 0; j < C; j++) {
            alunos = (int *) malloc(sizeof(int) * A);
            cidades[j] = alunos;
        }
        regioes[i] = cidades;
    }

    static const int defaults[3][4][6] = {  {   // Regiao 0
                                            {30, 40, 20, 80, 85, 10},
                                            {10, 20, 30, 40, 50, 60},
                                            {60, 50, 40, 30, 20, 10},
                                            {70, 55, 35, 80, 95, 27}
                                            },
                                            {   // Regiao 1
                                            {35, 45, 25, 85, 90, 15},
                                            {15, 25, 35, 45, 55, 65},
                                            {65, 55, 45, 35, 25, 15},
                                            {75, 60, 40, 85, 100, 32}
                                            },
                                            {   // Regiao 2
                                            {20, 30, 10, 70, 75, 0},
                                            {0, 10, 20, 30, 40, 50},
                                            {50, 40, 30, 20, 10, 0},
                                            {60, 45, 25, 70, 85, 17}
                                            } };
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            memcpy(regioes[i][j], defaults[i][j], sizeof(int) * A);
        }
    }
}


int comparador(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void ordena() { // Implementar o counting sort
    int i, j;
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            qsort(regioes[i][j], A, sizeof(int), comparador);
        }
    }
}

void escrever_matriz() {
    FILE *fp = NULL;
    int i, j, k;

    fp = fopen("./matriz_gerada.csv", "w");
    if (fp == NULL) {
        exit(1);
    }

    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            for (k = 0; k < A; k++) {
                fprintf(fp, "%d", regioes[i][j][k]);
                if (k < A-1) {
                    fprintf(fp, ",");
                }
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
}

void counting_sort(int *vetor, int *contagem) {
    for (int i = 0; i < A; i++) {
        contagem[vetor[i]]++;
    }

    int k = 0;
    for (int i = 0; i < NOTA_MAXIMA; i++) {
        for (int j = 0; j < contagem[i]; j++) {
            vetor[k++] = i;
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

#ifndef DEBUG
    // Leitura dos dados
    scanf("%d %d %d %d", &R, &C, &A, &SEED);

    // Definicao da semente aleatoria
    srand(SEED);

// Alocacao de memoria para os dados:
    // Geracao das matrizes
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

    // Geracao dos vetores de contagem
    contagem_regioes = (int **)malloc(sizeof(int *) * R);
    contagem_pais = (int *)calloc(NOTA_MAXIMA, sizeof(int));
    contagem_cidades = (int ***) malloc(sizeof(int**) * R);

    for (i = 0; i < R; i++) {
        // para cada região, um vetor de contagem para cada cidade
        contagem_cidades[i] = (int **) malloc(sizeof(int *) * C);
        for (j = 0; j < C; j++) {
            // para cada cidade, um vetor de contagem de cada nota
            contagem_cidades[i][j] = (int *) malloc(sizeof(int) * NOTA_MAXIMA);
        }
        contagem_regioes[i] = (int *)calloc(NOTA_MAXIMA, sizeof(int));
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

    escrever_matriz();

    // Calculo das estatisticas

    start_time = omp_get_wtime();

    // Impressão da matriz para depuração
    // printf("\nPRÉ-ORDENAÇÃO\n");
    // for (i = 0; i < R; i++) {
    //     for (j = 0; j < C; j++) {
    //         for (k = 0; k < A; k++) {
    //             printf("%d ", regioes[i][j][k]);
    //         }
    //         printf("\n");
    //     }
    // }
    // printf("\n");

    // Geração dos vetores de contagem
    for (i = 0; i < R; i++) {
        // gerar vetores de contagem para cada cidade
        for (j = 0; j < C; j++) {
            counting_sort(regioes[i][j], contagem_cidades[i][j]);
        }
        // para gerar o vetor de contagem da região, somar os 
        // vetores de cidade
        for (j = 0; j < C; j++) {
            for (k = 0; k < NOTA_MAXIMA; k++) {
                contagem_regioes[i][k] += contagem_cidades[i][j][k];
            }
        }
    }
    // para gerar o vetor de contagem do país, somar
    // os vetores de região
    for (i = 0; i < R; i++) {
        for (k = 0; k < NOTA_MAXIMA; k++) {
            contagem_pais[k] += contagem_regioes[i][k];
        }
    }

    time = omp_get_wtime() - start_time;

    // Impressão da matriz para depuração
    // printf("\nPÓS-ORDENAÇÃO\n");
    // for (i = 0; i < R; i++) {
    //     for (j = 0; j < C; j++) {
    //         for (k = 0; k < A; k++) {
    //             printf("%d ", regioes[i][j][k]);
    //         }
    //         printf("\n");
    //     }
    // }
    // printf("\n");


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
