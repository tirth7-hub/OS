#this file is the bridge b/w cpu hardware and c++ code

.set IRQ_BASE, 0x20

.section .text

.extern _ZN6MarkOS21hardwarecommunication16InterruptManager15HandleInterruptEhj #There is a function defined somewhere else. It isn't defined in this assembly file, but I'll call it.


.macro HandleException num  #this define assembly marco
.global _ZN6MarkOS21hardwarecommunication16InterruptManager19HandleException\num\()Ev
_ZN6MarkOS21hardwarecommunication16InterruptManager19HandleException\num\()Ev:
    movb $\num, (interruptnumber)
    jmp int_bottom
.endm


.macro HandleInterruptRequest num
.global _ZN6MarkOS21hardwarecommunication16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN6MarkOS21hardwarecommunication16InterruptManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptnumber) #"movb"- Move a byte
    pushl $0
    jmp int_bottom
.endm


HandleException 0x00
HandleException 0x01
HandleException 0x02
HandleException 0x03
HandleException 0x04
HandleException 0x05
HandleException 0x06
HandleException 0x07
HandleException 0x08
HandleException 0x09
HandleException 0x0A
HandleException 0x0B
HandleException 0x0C
HandleException 0x0D
HandleException 0x0E
HandleException 0x0F
HandleException 0x10
HandleException 0x11
HandleException 0x12
HandleException 0x13



HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x02
HandleInterruptRequest 0x03
HandleInterruptRequest 0x04
HandleInterruptRequest 0x05
HandleInterruptRequest 0x06
HandleInterruptRequest 0x07
HandleInterruptRequest 0x08
HandleInterruptRequest 0x09
HandleInterruptRequest 0x0A
HandleInterruptRequest 0x0B
HandleInterruptRequest 0x0C
HandleInterruptRequest 0x0D
HandleInterruptRequest 0x0E
HandleInterruptRequest 0x0F
HandleInterruptRequest 0x31

HandleInterruptRequest 0x80

int_bottom:

    # register
    #pusha  #Push all general-purpose 32-bit registers onto the stack.
    # pushl %ds
    # pushl %es
    # pushl %fs
    # pushl %gs
    pushl %ebp
    pushl %edi
    pushl %esi

    pushl %edx
    pushl %ecx
    pushl %eax
    # ring 0 segment register
    #cld -Clear the Direction Flag.
    #mov $0x10, %eax
    #mov %eax, %eds
    #mov %eax, %ees

    # call C++ Handler
    pushl %esp
    push (interruptnumber)
    call _ZN6MarkOS21hardwarecommunication16InterruptManager15HandleInterruptEhj
    #add %esp, 6
    mov %eax, %esp # stack pointer

    # restore registers

    pop %eax
    pop %ebx
    pop %ecx
    pop %edx

    pop %esi
    pop %edi
    pop %ebp
    # pop %gs
    # pop %fs
    # pop %es
    # pop %ds
    # popa

    add $4, %esp

.global _ZN6MarkOS21hardwarecommunication16InterruptManager15InterruptIgnoreEv  #mangled name
_ZN6MarkOS21hardwarecommunication16InterruptManager15InterruptIgnoreEv:

    iret   #the CPU automatically pushed interrupt-related state when entering the interrupt


.data
    interruptnumber: .byte 0
