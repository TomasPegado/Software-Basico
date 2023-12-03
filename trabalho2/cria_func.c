/*Tomas Lenzi 2220711 3WA*/
/*Gabriel Emile 2220498 3WB*/

#include <stdio.h>
#include <string.h>
#include <stdint.h> // Para intptr_t
#include "cria_func.h"

void cria_func(void *f, DescParam params[], int n, unsigned char codigo[]) {
    // Código de máquina base
    static const unsigned char codigo_base[] = {
        0x55, 0x48, 0x89, 0xe5, // Instruções iniciais
        0xbe, 0x0a, 0x00, 0x00, 0x00, // mov    $0xa,%esi
        0x48, 0xb8, // mov 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Espaço para ponteiro da funcao
        0xff, 0xd0, // call   *%rax
        0xc9, 
        0xc3 // leaveq e retq
    };                  

    memcpy(codigo, codigo_base, sizeof(codigo_base));
     __builtin___clear_cache (codigo, codigo + sizeof(codigo_base)); 

    // Inserção do ponteiro
    memcpy(&codigo[11], &f, sizeof(intptr_t));

}
