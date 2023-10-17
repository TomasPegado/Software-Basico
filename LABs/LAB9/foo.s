/*
void foo (int a[], int n) {
  int i;
  int s = 0;
  for (i=0; i<n; i++) {
    s += a[i];
    if (a[i] == 0) {
      a[i] = s;
      s = 0;
    }
  }
} */

.text
.global foo

foo:
/* prologo */
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movl $0, %ebx
    movl $0, %edx
    FOR:
    cmpl %ebx, %esi
    je FIM

    addl (%rdi), %edx /*s += a[i] */
    cmpl $0, (%rdi)
    jne LOOP

    movl %edx, (%rdi)
    movl $0, %edx
    jmp LOOP

    LOOP:
    addl $1, %ebx
    addq $4, %rdi
    jmp FOR
    FIM:
    leave
    ret
