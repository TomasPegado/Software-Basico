#include <stdio.h>


int utf2varint(FILE *arq_entrada, FILE *arq_saida){
    char linha[1024]; // Buffer para armazenar cada linha lida

    while (fgets(linha, sizeof(linha), arq_entrada) != NULL) {
        // Processa a linha aqui, por enquanto, apenas imprimimos
        printf("%s", linha);
    }

    // Se o loop terminou devido a um erro de leitura, tratamos isso
    if (ferror(arq_entrada)) {
        fprintf(stderr, "Erro ao ler o arquivo.\n");
        return -1; // Retorno de erro
    }

    return 0; // Sucesso
}

int varint2utf(FILE *arq_entrada, FILE *arq_saida){
    return 0;
}