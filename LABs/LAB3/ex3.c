#include <stdio.h>

unsigned char switch_byte(unsigned char x) {
  // Isola a metade superior do byte (4 bits mais significativos)
  unsigned char metade_superior = x >> 4;

  // Isola a metade inferior do byte (4 bits menos significativos)
  unsigned char metade_inferior = x << 4;

  // Combina as duas metades trocadas
  return metade_superior | metade_inferior;
}

int main() {
  unsigned char original = 0xAB;
  unsigned char resultado = switch_byte(original);

  printf("Original: 0x%02X\n", original);
  printf("Trocado:  0x%02X\n", resultado);

  return 0;
}
