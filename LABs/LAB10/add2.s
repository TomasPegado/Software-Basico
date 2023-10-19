/*
int add2 (struct X *x) {
  if (x == NULL) return 0;
  else return x->val + add2(x->next);
} */

.text
.global add2

add2:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    cmpq $0, %rdi
    jne ELSE
    
    movl $0, %eax
    leave
    ret

ELSE:
    movq %rdi, -8(%rbp)
    movq 8(%rdi), %rdi
    call add2
    movq -8(%rbp), %rdi
    addl (%rdi), %eax

    leave
    ret