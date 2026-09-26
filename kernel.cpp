void printf(char* str){
    unsigned short* VideoMemory = (unsigned short*)0xb8000; //VGA text-mode framebuffer begins at this address.    occupies 16bits=2byte
    for(int i=0;str[i] != '\0'; i++){//loop for travelling the whole string
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
    }
}

extern "C" void kernelMain(void* multboot_structure, unsigned int magicnumber){
    printf("hello world! --Tirth Patel");

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
