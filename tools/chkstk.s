.text
.globl __chkstk
.p2align 4, 0x90
__chkstk:
    pushq %rcx
    pushq %rax
    cmpq $0x1000, %rax
    leaq 0x18(%rsp), %rcx
    jb 2f
1:
    subq $0x1000, %rcx
    testb $0, (%rcx)
    subq $0x1000, %rax
    cmpq $0x1000, %rax
    ja 1b
2:
    subq %rax, %rcx
    testb $0, (%rcx)
    popq %rax
    popq %rcx
    retq
