.text
.global mult

mult:
    pushq %rbp
    movq %rsp, %rbp

    imull %esi, %edi
    movl %edi, %eax

    leave
    ret