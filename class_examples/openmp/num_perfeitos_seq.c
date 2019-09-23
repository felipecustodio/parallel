#include <stdio.h>
#include <stdlib.h>

#define NUM 100000

int main() {
    int i, j;
    for (i = 1; i < NUM; i++){
        int soma = 0;
        for (j = 1; j < i; j++){
            if(i%j == 0){
                soma += j;
            }
        }
        if (soma == i){
            printf("%d é perfeito. \n", i);
        }
    }

    return 0;
}