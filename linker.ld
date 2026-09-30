ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)  /*this tells the linker to produce a 32bit ELf executable for the i386 architecture*/
OUTPUT_ARCH(i386:i386)  /*we werebuilding a 32bit x86 kernel*/

SECTIONS
{
  . = 0x0100000; /*"."-current location , start placing the kernel at address 0x100000*/

  .text :
  {
    *(.multiboot)   /* take the .multiboot section from the input object files and place it here*/
    *(.text*)  /* "*"-serach all input object files to match*/
    *(.rodata)/* read only data*/
  }

  .data  :
  {
    start_ctors = .;
    KEEP(*( .init_array ));  /*this tells the linker to keep .ini_array section*/
    KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));/*this handle .init_array. section and sort them according to initialization priority.*/
    end_ctors = .;

    *(.data)
  }

  .bss  :   /*this collect .bss section from your object files*/
  {
    *(.bss)
  }

  /DISCARD/ : { *(.fini_array*) *(.comment) }  /* this section should not appear in the final kernel*/
}
/*                linker.ld       lecture-1
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
