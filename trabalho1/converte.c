/* 
Integrantes
Nome: Tomás Lenzi, Matricula: 2220711, Turma: 3WA
Nome: Gabriel Emile, Matricula: 2220498, Turma: 3WB
*/

#include <stdio.h>
#include <stdbool.h>

// ********* UTF8 para Varint ********* //

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

// Função para converter um caractere UTF-8 em seu codepoint Unicode
unsigned int utf8_to_codepoint(unsigned char *bytes, int length) {
    if (length == 1) {
        return bytes[0];
    } else if (length == 2) {
        return ((bytes[0] & 0x1F) << 6) |
               (bytes[1] & 0x3F);
    } else if (length == 3) {
        return ((bytes[0] & 0x0F) << 12) |
               ((bytes[1] & 0x3F) << 6)  |
               (bytes[2] & 0x3F);
    } else if (length == 4) {
        return ((bytes[0] & 0x07) << 18) |
               ((bytes[1] & 0x3F) << 12) |
               ((bytes[2] & 0x3F) << 6)  |
               (bytes[3] & 0x3F);
    }
    return 0;  // valor inválido
}

// Codifica um número inteiro em varint e escreve os bytes resultantes no buffer
int encode_varint(unsigned int value, unsigned char *buffer) {
    int buffer_length = 0;

    do {
        buffer[buffer_length] = (unsigned char)(value & 0x7F);
        value >>= 7;
        
        if (value != 0) {
            buffer[buffer_length] |= 0x80;
        }
        
        buffer_length++;
    } while (value);

    return buffer_length; // Retorna o número de bytes escritos
}

int utf2varint(FILE *arq_entrada, FILE *arq_saida){

    unsigned char bytes[4];
    unsigned char varint_buffer[5]; // Para armazenar o valor varint codificado
    int ch;
    while ((ch = fgetc(arq_entrada)) != EOF) {
        int length = utf8_char_length(ch);
        if (length == 0) {
            fprintf(stderr, "Byte inválido para UTF-8: %x\n", ch);
            return -1;
        }

        bytes[0] = ch;
        for (int i = 1; i < length; i++) {
            ch = fgetc(arq_entrada);
            if (ch == EOF) {
                fprintf(stderr, "EOF inesperado durante a leitura de um caractere UTF-8.\n");
                return -1;
            }
            bytes[i] = ch;
        }

        unsigned int codepoint = utf8_to_codepoint(bytes, length);
        int varint_length = encode_varint(codepoint, varint_buffer);

        // Escreve a codificação varint no arquivo de saída
        fwrite(varint_buffer, sizeof(unsigned char), varint_length, arq_saida);

    }

    if (ferror(arq_entrada)) {
        fprintf(stderr, "Erro ao ler o arquivo.\n");
        return -1;
    }
    if (ferror(arq_saida)) {
        fprintf(stderr, "Erro ao escrever o arquivo.\n");
        return -1;
    }
    return 0; // Sucesso
}

// ********* Varint pra UTF8 ********* //

// Decodifica um varint e retorna o valor inteiro resultante
unsigned int decode_varint(unsigned char *buffer, int length) {
    unsigned int value = 0;
    for (int i = 0; i < length; i++) {
        value |= (buffer[i] & 0x7F) << (7 * i);
    }
    return value;
}

// Codifica um codepoint em UTF-8 e retorna o número de bytes escritos
int codepoint_to_utf8(unsigned int codepoint, unsigned char *buffer) {
    if (codepoint < 0x80) {
        buffer[0] = codepoint;
        return 1;
    } else if (codepoint < 0x800) {
        buffer[0] = 192 | (codepoint >> 6);
        buffer[1] = 128 | (codepoint & 63);
        return 2;
    } else if (codepoint < 0x10000) {
        buffer[0] = 224 | (codepoint >> 12);
        buffer[1] = 128 | ((codepoint >> 6) & 63);
        buffer[2] = 128 | (codepoint & 63);
        return 3;
    } else {
        buffer[0] = 240 | (codepoint >> 18);
        buffer[1] = 128 | ((codepoint >> 12) & 63);
        buffer[2] = 128 | ((codepoint >> 6) & 63);
        buffer[3] = 128 | (codepoint & 63);
        return 4;
    }
}

int varint2utf(FILE *arq_entrada, FILE *arq_saida){

    unsigned char buffer[5];         // Para armazenar os bytes varint
    unsigned char utf8_buffer[4];    // Para armazenar a representação UTF-8
    int byte_count = 0;              // Contador de bytes do varint atual

    while (true) {
        int ch = fgetc(arq_entrada);
        if (ch == EOF) break;

        buffer[byte_count++] = (unsigned char)ch;

        if (ch < 128) { // Detectou o final de uma sequência varint
            unsigned int codepoint = decode_varint(buffer, byte_count);
            int utf8_length = codepoint_to_utf8(codepoint, utf8_buffer);
            fwrite(utf8_buffer, sizeof(unsigned char), utf8_length, arq_saida);
            
            // Reset para a próxima sequência varint
            byte_count = 0;
        }
    }

    if (ferror(arq_entrada)) {
        fprintf(stderr, "Erro ao ler o arquivo.\n");
        return -1;
    }
    if (ferror(arq_saida)) {
        fprintf(stderr, "Erro ao escrever o arquivo.\n");
        return -1;
    }

    return 0;
}