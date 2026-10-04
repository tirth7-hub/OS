ENTRY(loader)   /*The entry point of this executable is loader*/
OUTPUT_FORMAT(elf32-i386)  /*this create a 32-bit ELF executable for i386.*/
OUTPUT_ARCH(i386:i386)  /*building a 32bit x86 kernel*/

SECTIONS
{
  . = 0x0100000; /*"."-current location , start placing the kernel at address 0x0100000 = 1MiB into memory*/

  .text :  /*collects code and related sections.*/
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

  .bss  :   /*this section contains uninitialized global/static data.*/
  {
    *(.bss)
  }

  /DISCARD/ : { *(.fini_array*) *(.comment) }  /* this section should not appear in the final kernel*/
}
