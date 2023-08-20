#include <ctype.h>
#include <stdio.h>

int charToValue(char c);

int string2num(char *s, int base) {
  int a = 0;
  for (; *s; s++) {
    int value = charToValue(*s);
    if (value >= 0 && value < base) {
      a = a * base + value;
    } else {
      // Caractere inválido para a base
      return -1;
    }
  }
  return a;
}

int main (void) {
     printf("%d\n", string2num("999a", 16));
     printf("%d\n", string2num("a09b", 16));
     printf("%d\n", string2num("z09b", 64));
  return 0;
}