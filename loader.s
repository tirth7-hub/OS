.set MAGIC, 0x1badb002     #it is multiboot magic number, GRUB looks for the multiboot header
.set FLAGS, (1<<0 | 1<<1)  # These specify requested Multiboot features
.set CHECKSUM, -(MAGIC + FLAGS) # multiboot header require checksum relation ship MAGIC + FLAGS + CHECKSUM = 0

.section .multiboot  #this place the multiboot header into kernel , linker does contain *(.multiboot)
    .long MAGIC
    .long FLAGS
    .long CHECKSUM


.section .text
.extern kernelMain   #"extern"-this symbol exists someware else. it is in kernel.cpp
.extern callConstructors   #"extern"-this symbol exists someware else. it is in kernel.cpp
.global loader


loader:    #this is the entry point specified by ENTRY(loader) in linker.ld file.   chain is:  linker.id->Entry(loader)->loader.s->loader:
    mov $kernel_stack, %esp  # "esp"-cpu stack pointer
    call callConstructors  #call callConstructors() function in  kernel.cpp file. linker file collect constructor info. into .init_array and function walk through it
    push %eax     #EAX = multiboot magic
    push %ebx     #EBX = address of multiboot information structure
    call kernelMain  # call Because x86 32-bit calling convention passes arguments on the stack


_stop:
    cli   # Clear the CPU interrupt flag -  Disable maskable hardware interrupts
    hlt   #Halt the CPU until an interrupt or other wake-up condition.
    jmp _stop


.section .bss     #the kernel_stack storage is here
.space 2*1024*1024; # 2 MiB reserve
kernel_stack:  #The stack grows downward on x86, so starting ESP at the address labeled kernel_stack is intentional
