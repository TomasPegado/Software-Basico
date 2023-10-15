#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

typedef struct X {
  int a;
  short b;
  int c;
} x;

int main (void) {
  x objeto;
  objeto.a = 2;
  objeto.b = 1;
  objeto.c = 12;

  dump(&objeto, sizeof(objeto));
  return 0;
}