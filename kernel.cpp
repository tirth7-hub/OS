
#include "types.h"
#include "gdt.h"
#include "interrupts.h"

void printf(char* str)
{
  static uint16_t* VideoMemory = (uint16_t*)0xb8000; //VGA text-mode framebuffer begins at this address.    occupied 16bits = 2byte

  static uint8_t x=0,y=0;   //setting initial values for the SCREEN. Generally screen is 80 character wide and 25 height

  for(int i = 0; str[i] != '\0'; ++i) // loop for travelling the whole sting
  {
    switch(str[i])
    {
      case '\n':
        x = 0;
        y++;
        break;
      default:
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
        x++;
        break;
    }

    if(x >= 80) //if one line complete(x=80) than move to next line(y++)  and set  x=0 again
    {
      x = 0;
      y++;
    }

    if(y >= 25) //
    {
      for(y = 0; y < 25; y++)
        for(x = 0; x < 80; x++)
          VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';  //loops for setting back to all clear screen
      x = 0;
      y = 0;
    }
  }
}



typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
  for(constructor* i = &start_ctors; i != &end_ctors; i++)
    (*i)();
}



extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
  printf("Hello\n");

  GlobalDescriptorTable gdt;
  InterruptManager Interrupts(0x20, &gdt);
  Interrupts.Activate();

  while(1);
}
/*      BOOT        lecture-1
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
