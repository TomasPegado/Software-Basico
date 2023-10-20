#include <stdio.h>
#include <stdbool.h>

// Decodifica um varint e retorna o valor inteiro resultante
unsigned int decode_varint(unsigned char *buffer, int length) {
    unsigned int value = 0;
    for (int i = 0; i < length; i++) {
        value |= (buffer[i] & 0x7F) << (7 * i);
    }
    return value;
}

void testVarintDecoding(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", filename);
        return;
    }

    unsigned char buffer[5];
    int byte_count = 0;

    while (true) {
        int ch = fgetc(file);
        if (ch == EOF) break;

        buffer[byte_count++] = (unsigned char)ch;

        if (ch < 128) {
            // Terminou uma sequência varint
            unsigned int codepoint = decode_varint(buffer, byte_count);
            printf("Varint decodificado: U+%04X\n", codepoint);

            byte_count = 0;
        }
    }

    fclose(file);
}

int main() {
    // Testa a decodificação varint
    testVarintDecoding("saida_varint.bin");

    return 0;
}
