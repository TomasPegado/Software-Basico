#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

int main ()
{
  char code[] = {
    0x8D, 0x04, 0x37,           //  lea eax,[rdi+rsi]
    0xC3                        //  ret
  };

  int (*sum) (int, int) = NULL;

  // allocate executable buffer                                             
  sum = mmap (0, sizeof(code), PROT_READ|PROT_WRITE|PROT_EXEC,
              MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

  // copy code to buffer
  memcpy (sum, code, sizeof(code));
  // doesn't actually flush cache on x86, but ensure memcpy isn't
  // optimized away as a dead store.
  __builtin___clear_cache (sum, sum + sizeof(sum));  // GNU C

  // run code
  int a = 2;
  int b = 3;
  int c = sum (a, b);

  printf ("%d + %d = %d\n", a, b, c);
}