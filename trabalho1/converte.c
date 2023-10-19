#include <stdio.h>
#include <stdbool.h>

// Função auxiliar para imprimir a representação binária de um byte
void printBinary(unsigned char ch) {
    for (int i = 7; i >= 0; i--) {
        putchar((ch & (1 << i)) ? '1' : '0');
    }
}

// Função auxiliar para determinar quantos bytes um caractere UTF-8 ocupa
int utf8_char_length(unsigned char ch) {
    if ((ch & 0x80) == 0) return 1;      // 0xxxxxxx
    if ((ch & 0xE0) == 0xC0) return 2;   // 110xxxxx
    if ((ch & 0xF0) == 0xE0) return 3;   // 1110xxxx
    if ((ch & 0xF8) == 0xF0) return 4;   // 11110xxx
    return 0;  // Não é um byte inicial válido para UTF-8
}

int utf2varint(FILE *arq_entrada, FILE *arq_saida){
    // char linha[1024]; // Buffer para armazenar cada linha lida

    // while (fgets(linha, sizeof(linha), arq_entrada) != NULL) {
    //     // Processa a linha aqui, por enquanto, apenas imprimimos
    //     printf("%s", linha);
    // }

    // // Se o loop terminou devido a um erro de leitura, tratamos isso
    // if (ferror(arq_entrada)) {
    //     fprintf(stderr, "Erro ao ler o arquivo.\n");
    //     return -1; // Retorno de erro
    // }

    int ch;
    while ((ch = fgetc(arq_entrada)) != EOF) {
        int length = utf8_char_length(ch);
        if (length == 0) {
            fprintf(stderr, "Byte inválido para UTF-8: %x\n", ch);
            return -1;
        }

        // Imprima o caractere em binário
        printf("0x%x - ", ch);
        printBinary(ch);

        // Leia e imprima os bytes restantes deste caractere, se houver
        for (int i = 1; i < length; i++) {
            ch = fgetc(arq_entrada);
            if (ch == EOF) {
                fprintf(stderr, "EOF inesperado durante a leitura de um caractere UTF-8.\n");
                return -1;
            }
            printf(" ");
            printBinary(ch);
        }

        printf("\n");
    }

    if (ferror(arq_entrada)) {
        fprintf(stderr, "Erro ao ler o arquivo.\n");
        return -1;
    }


    return 0; // Sucesso
}

int varint2utf(FILE *arq_entrada, FILE *arq_saida){
    return 0;
}