#include <stdio.h>
#include <stdbool.h>
#include "converte.h"

void testeFuncao(FILE *arq){

    FILE *saida = fopen("saida.txt", "w");
    int t = utf2varint(arq, saida);
    if (t==0){
        printf("teste passou\n");
    } else {
        fprintf(stderr, "Teste Falhou\n");
    }
}

int main(void){

    FILE *arq = fopen("utf8_peq.txt", "r");
    testeFuncao(arq);
    return 0;
}