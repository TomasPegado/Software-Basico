#include <stdio.h>

int odd_ones(unsigned int x) {
  
  int count = 0;
  while (x) {
    count += x & 1;
    x >>= 1;
  }
  int impar = count & 1;
  if (impar == 1) {
    return 1;
  }
  else return 0;
}
int main() {
  printf("%x tem numero %s de bits\n",0x01010101,odd_ones(0x01010101) ? "impar":"par");
  printf("%x tem numero %s de bits\n",0x01030101,odd_ones(0x01030101) ? "impar":"par");
  return 0;
}