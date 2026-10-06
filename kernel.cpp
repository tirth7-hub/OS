
#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "keyboard.h"
#include "mouse.h"

void printf(char* str)
{
  static uint16_t* VideoMemory = (uint16_t*)0xb8000; //0xB8000 is the conventional physical address of the VGA text-mode framebuffer. each screen cell is 16bit

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
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i]; //This preserves the upper 8 bits containing the color and replaces the lower 8 bits with the character
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



typedef void (*constructor)();   //constructor is a pointer to a function returning void
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
  for(constructor* i = &start_ctors; i != &end_ctors; i++)  //loop walks through all registered constructors.
    (*i)();  //call each constructor
}



extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/) //kernel's c++ starting point'
{
  printf("Hello\n");
  printf("Good Morning Sir!");
  GlobalDescriptorTable gdt;
  InterruptManager Interrupts(0x20, &gdt);  //0x20-32 decimal, This is the interrupt number where you want hardware IRQs to begin
  KeyboardDriver keyboard(&Interrupts); //call KeyboardDriver function in keyboard.cpp file
  MouseDriver mouse(&Interrupts); //call KeyboardDriver function in keyboard.cpp file
  Interrupts.Activate();  // this call the Activte function that run sti(set interrupt flag) cpu may now accept maskable hardware interrupts.

  while(1); //this is infinite loop , this os currently has nothing to do in this main kernel thread but interrupt can occur Activate function enable them

  // kernelMain:
  //   forever:
  //       do nothing
  //     meanwhile:
  //       keyboard interrupt
  //           |
  //       handle key
  //           |
  //       return
  //           |
  //       continue infinite loop
}

