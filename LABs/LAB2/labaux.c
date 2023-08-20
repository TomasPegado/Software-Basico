#include <ctype.h>
int charToValue(char c) {
  if (isdigit(c))
    return c - '0';
  else if (isalpha(c))
    return toupper(c) - 'A' + 10;
  else
    return -1; // Caractere inválido
}