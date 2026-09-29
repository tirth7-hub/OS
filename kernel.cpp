#include "types.h"
#include "gdt.h"
void printf(char* str){
    static uint16_t* VideoMemory = (uint16_t*)0xb8000; //VGA text-mode framebuffer begins at this address.    occupies 16bits=2byte
    for(int i=0;str[i] != '\0'; i++){//loop for travelling the whole string
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
    }
}

typedef void (*constructors)();
extern "c" constructors start_ctors;
extern "c" constructors end_ctors;
extern "c" void callconstructors(){
  for(constructors* i = &start_ctors; i != end_ctors; i++){
    (*i)();
  }
}

extern "C" void kernelMain(void* multboot_structure, uint32_t magicnumber){
    printf("hello world! --Tirth Patel");

    GlobalDescriptorTable gdt;

    while(1);
}


/* BOOT        lecture-1
    │
    ▼
   Bootloader / assembly
    │
    │ calls kernelMain()
    ▼
  ┌─────────────────┐
  │   kernelMain()  │
  └────────┬────────┘
    │
    ▼
  printf("hello world...")
    │
    ▼
  0xB8000 VGA memory
    │
    ▼
  VGA hardware
    │
    ▼
  SCREEN */
