#include <stdio.h>
#include <stdbool.h>
#include "converte.h"



int main() {
    FILE *arq_entrada = fopen("utf8_peq.txt", "rb");
    FILE *arq_saida = fopen("saida_varint.bin", "wb");
    if (!arq_entrada || !arq_saida) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    utf2varint(arq_entrada, arq_saida);
    fclose(arq_entrada);
    fclose(arq_saida);

    return 0;
}