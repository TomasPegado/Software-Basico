/*
struct X {
  int val;
  struct X *next;
};

int add (struct X *x) {
  int a = 0;
  for (; x != NULL; x = x->next)
    a += x->val;
  return a;
} */

.text
.global add

add:
    /*prologo */

    pushq %rbp
    movq %rsp, %rbp

    movl $0, %eax /*int a = 0 */
    FOR:
    cmpq $0, %rdi /*x == NULL? (NULL é interpretado como 0)  */
    je FIM

    addl (%rdi), %eax  /* Desenho da struct-> val val val val x x x x next next next next next next next next */
                          /* a = a+(*x) */
    movq 8(%rdi), %rdi /* rdi <- (rdi + 8) */ /* Estou movendo rdi 8 endereços depois (pra pegar o next da próxima)*/
    jmp FOR

    FIM:
    leave
    ret