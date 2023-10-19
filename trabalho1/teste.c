#include <stdio.h>
#include "converte.h"

void testLeitura(FILE *arq){

    FILE *saida = fopen("saida.txt", "w");
    int t = utf2varint(arq, saida);
    if (t==0){
        printf("teste passou\n%d",t);
    } else {
        fprintf(stderr, "Teste Falhou\n");
    }
}

int main(void){

    FILE *arq = fopen("utf8_peq.txt", "rb");
    testLeitura(arq);
    return 0;
}