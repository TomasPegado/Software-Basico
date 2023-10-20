#include <stdio.h>
#include "converte.h"



int main() {
    FILE *arq_entrada = fopen("var_demo", "rb");
    FILE *arq_saida = fopen("saida_utf8_demo.bin", "wb");
    if (!arq_entrada || !arq_saida) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    varint2utf(arq_entrada, arq_saida);
    fclose(arq_entrada);
    fclose(arq_saida);

    return 0;
}