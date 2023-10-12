#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


// Questao 1
// void dump (void *p, int n) {
//   unsigned char *p1 = p;
//   while (n--) {
//     printf("%p - %02x\n", p1, *p1);
//     p1++;
//   }
// }

// int main (void) {
//   char c = 150;
//   short s = -3;
//   int i = -151;
//   printf("dump de c: \n");
//   dump(&c, sizeof(c));
//   printf("dump de s: \n");
//   dump(&s, sizeof(s));
//   printf("dump de i: \n");
//   dump(&i, sizeof(i));
//   return 0;
// }


//Questao 2 
// void dump (void *p, int n) {
//   unsigned char *p1 = p;
//   while (n--) {
//     printf("%p - %02x\n", p1, *p1);
//     p1++;
//   }
// }

// int main (void) {
//   short l = -32765;
//   unsigned short k = 3434;
//   printf("l=%d, k=%u \n", l, k);
//   printf("dump de l: \n");
//   dump(&l, sizeof(l));
//   printf("dump de k: \n");
//   dump(&k, sizeof(k));
//   return 0;
// }


typedef unsigned packed_t;

int string2num (char *s, int base) {
  int a = 0;
  for (; *s; s++) {
    if(isdigit(*s))
      a = a*base + (*s - '0');
    else if((*s >= 'A') && (*s < (base-10+'A')))
      a = a*base + ((*s - 'A') + 10);
    else if((*s >= 'a') && (*s < (base-10+'a')))
      a = a*base + ((*s - 'a') + 10);
    else {
      printf("pane: numero invalido! \n");
      exit(1);
    }
  }
  return a;
}

int xbyte (packed_t word, int bytenum) {
  int byte_shifted = word >> (bytenum << 3); // Deslocamento para pegar o byte desejado nos bits menos significativos.
    int sign_bit = 0x80 & byte_shifted; // Pega o bit mais significativo do byte.
    if (sign_bit) {
        return byte_shifted | ~0xFF; // Estende o sinal preenchendo com 1s à esquerda.
    } else {
        return byte_shifted & 0xFF; // Garante que apenas os bits do byte sejam retornados.
    }
  return 1;
}

int main (int argc, char **argv) {
  int x;
  if (argc != 3) {
    printf ("uso: %s <word (em hexadecimal)> <bytenum>\n", argv[0]);
    exit(1);
  }

  x = xbyte(string2num(argv[1], 16), atoi(argv[2]));
  printf ("%08x  %d\n", x, x);
  return 0;
}

