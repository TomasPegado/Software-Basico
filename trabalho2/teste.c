#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h> 
#include "cria_func.h"

typedef int (*func_ptr) (int x);

int mult(int x, int y) {
  return x * y;
}

int main() {
    unsigned char* codigo;
    // allocate executable buffer                                             
    codigo = mmap (0, 1024, PROT_READ|PROT_WRITE|PROT_EXEC,
              MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    DescParam params[2]; // Configurar de acordo com sua estrutura

    params[0].tipo_val = INT_PAR; /* o primeiro parãmetro de mult é int */
    params[0].orig_val = PARAM;   /* a nova função repassa seu parämetro */

    params[1].tipo_val = INT_PAR; /* o segundo parâmetro de mult é int */
    params[1].orig_val = FIX;     /* a nova função passa para mult a constante 10 */
    params[1].valor.v_int = 10;

    cria_func(mult, params, 2, codigo);

    // Converter 'codigo' para um ponteiro de função e executar
    func_ptr func = (func_ptr)codigo;

    for (int i=0; i<11; i++){
      int result = (func)(i); // tabela
      printf("Resultado: %d\n", result);
    }
    

    return 0;
}