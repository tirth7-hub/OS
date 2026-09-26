ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)   /*This tells the linker to produce a 32-bit ELF executable for the i386 architecture.*/
OUTPUT_ARCH(i386:i386)  /*We're building a 32-bit x86 kernel.*/

SECTIONS
{
    . = 0x100000;  /* "."-current location , Start placing the kernel at address 0x100000*/
    .text :
    {
        *(.multiboot)  /*Take the .multiboot section from the input object files and place it here.*/
        *(.text*)  /* "*"-Search all input object files to match.*/
        *(.rodata)  /*read-only data*/
    }
    .data :
    {
        start_ctors = .;
        KEEP(*( .init_array ));   /*This tells the linker to keep .init_array sections.

.init_array is commonly used to store pointers to initialization functions, including C++ initialization machinery.

The KEEP() is important when linker garbage collection is enabled.*/
        KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.*))); /*This handles .init_array.* sections and sorts them according to initialization priority.*/
        end_ctors= .;
        *(.data)
    }
    .bss :
    {
        *(.bss)/*This collects .bss sections from your object files.*/
    }

    /DISCARD/ :/*These sections should not appear in the final kernel.*/
    {
        *(.fini_array*)
        *(.comment)
    }
}

/*                 linker.ld       lecture-1
                     │
        ┌────────────┴────────────┐
        │                         │
     loader.o                  kernel.o
        │                         │
        ├── .multiboot            ├── .text
        ├── .text                 ├── .rodata
        └── ...                   └── .data
        │                         │
        └────────────┬────────────┘
                     │
                     ▼
              ┌─────────────┐
              │    LINKER   │
              └──────┬──────┘
                     │
                     ▼
             kernel executable
                     │
                     ▼
                 0x100000
                  (1 MiB)       */

