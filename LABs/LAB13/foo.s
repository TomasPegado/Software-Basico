/*
int foo (int x) {
  return x+1;
} */


.text
.global foo

foo:

    pushq %rbp
    movq %rsp, %rbp

    incl %edi
    movl %edi, %eax

    leave
    ret