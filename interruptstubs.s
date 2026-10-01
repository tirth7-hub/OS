# visit - http://www.lowlevel.eu/wiki/Tyndur
# 'nm interrupts.o' for getting this key "_ZN16InterruptManager15handleInterruptEhj"
.set IRQ_BASE, 0x20
.section .text
.extern _ZN16InterruptManager15handleInterruptEhj #name of this handle interrupt. Now we can jmp to this assembler file
.global _ZN16InterruptManager22IgnoreInterruptRequestEv



.macro HandleException num
.global _ZN16InterruptManager16HandleException\num\()Ev
_ZN16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num, (interruptnumber)
    jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptnumber)
    jmp int_bottom
.endm



HandleInterruptRequest 0x00
HandleInterruptRequest 0x01

int_bottom:
    pusha  #registers
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs


    pushl %esp     # help to clean the stack
    push (interruptnumber)
    call _ZN16InterruptManager15handleInterruptEhj
    # addl $5, %esp
    movl %eax, %esp


    popl %gs  #registers
    popl %fs
    popl %es
    popl %ds
    popa

_ZN16InterruptManager22IgnoreInterruptRequestEv:
    iret    #return

.data
    interruptnumber: .byte 0

