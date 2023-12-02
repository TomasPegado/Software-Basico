/*int retorno(int i):

return i; */
.text
.global teste
teste:

    pushq %rbp
    movq %rsp, %rbp

    mov 0xcafe1234cafe1234, %rax

    call *%rax

    leave
    ret

