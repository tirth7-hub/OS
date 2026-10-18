
#include <common/types.h>
#include <gdt.h>
#include <memorymanagement.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/pci.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/driver.h>
#include <drivers/vga.h>
#include <gui/desktop.h>
#include <gui/window.h>
#include <gui/render.h>
#include <multitasking.h>


using namespace MarkOS;
using namespace MarkOS::common;
using namespace MarkOS::drivers;
using namespace MarkOS::hardwarecommunication;
using namespace MarkOS::gui;

// #define GRAPHICSMODE

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








void printfHex(uint8_t key){

  char* foo = "00";
  char* hex = "0123456789ABCDEF";
  foo[0] = hex[(key >> 4) & 0xF];
  foo[1] = hex[key & 0xF];
  printf(foo);
}

class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
  void OnKeyDown(char c)
  {
    char* foo =" ";
    foo[0]= c;
    printf(foo);
  }
};



class MouseToConsole : public MouseEventHandler
{
      int8_t x, y;
public:
    MouseToConsole()
    {

    }
    void OnMouseMove(int xoffset,int yoffset)
    {
      uint16_t* VideoMemory = (uint16_t*)0xb8000;
      x=40;
      y=12;
      VideoMemory[80*y+x] = ((VideoMemory[80*y+x] & 0xF000) >> 4)
      | ((VideoMemory[80*y+x] & 0x0F00) << 4)
      | ((VideoMemory[80*y+x] & 0x00FF));


      x += xoffset;
      if(x<0) x =0;
      if(x>=80) x=79;


      y -= yoffset;
      if(y<0) y =0;
      if(y>=25) y=24;

      VideoMemory[80*y+x] = ((VideoMemory[80*y+x] & 0xF000) >> 4)
      | ((VideoMemory[80*y+x] & 0x0F00) << 4)
      | ((VideoMemory[80*y+x] & 0x00FF));



    }
};



void taskA()
{
  while(true)
    printf("A");
}

void taskB()
{
  while(true)
    printf("B");
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

  GlobalDescriptorTable gdt;
  uint32_t* memupper = (uint32_t*)(((size_t)multiboot_structure) + 8);
  size_t heap = 10*1024*1024; //10 mb

  MemoryManager memoryManager(heap, (*memupper)*1024 - heap - 10*1024);

  printf("head: 0x");
  printfHex((heap >> 24) & 0xFF);
  printfHex((heap >> 16) & 0xFF);
  printfHex((heap >> 8 ) & 0xFF);
  printfHex((heap    ) & 0xFF);

  void* allocated = memoryManager.malloc(1024);
  printf("\nallocated: 0x");
  printfHex(((size_t)allocated >> 24) & 0xFF);
  printfHex(((size_t)allocated >> 16) & 0xFF);
  printfHex(((size_t)allocated >> 8 ) & 0xFF);
  printfHex(((size_t)allocated    ) & 0xFF);
  printf("\n");


  TaskManager taskManager;
  // Task task1(&gdt, taskA);
  // Task task2(&gdt, taskB);
  // taskManager.AddTask(&task1);
  // taskManager.AddTask(&task2);

  InterruptManager Interrupts(0x20, &gdt, &taskManager);  //0x20-32 decimal, This is the interrupt number where you want hardware IRQs to begin
  printf("initialized hardware!,stage-1\n");
#ifndef GRAPHICSMODE
  Desktop desktop (320,200,0x00,0x00,0xA8);
#endif
  DriverManager drvManager;
#ifndef GRAPHICSMODE
  PrintfKeyboardEventHandler kbhandler;


  //KeyboardDriver keyboard(&Interrupts, &kbhandler); //call KeyboardDriver function in keyboard.cpp file
  KeyboardDriver keyboard(&Interrupts, &desktop); //call KeyboardDriver function in keyboard.cpp file
#endif
  drvManager.AddDriver(&keyboard);

#ifndef GRAPHICSMODE
  MouseEventHandler mousehandler;
  //MouseDriver mouse(&Interrupts, &mousehandler); //call KeyboardDriver function in keyboard.cpp file

  MouseDriver mouse(&Interrupts, &desktop); //call KeyboardDriver function in keyboard.cpp file
#endif
  drvManager.AddDriver(&mouse);

  PeripheralComponentInterconnectController PCIController;
  PCIController.SelectDrivers(&drvManager, &Interrupts);

  VideoGraphicsArray vga;

  Render rend(320,200);
  printf("initialized hardware!,stage-2\n");
  drvManager.ActivateAll();

  printf("initialized hardware!,stage-3\n");

#ifndef GRAPHICSMODE

  vga.SetMode(320,200,8);

  Window win1(&desktop,10, 20, 20, 20, 0xA8,0x00,0x00);
  desktop.AddChild(&win1);
  Window win2(&desktop,40, 15, 30, 30, 0x00,0xA8,0x00);
  desktop.AddChild(&win2);
#endif
  Interrupts.Activate();  // this call the Activte function that run sti(set interrupt flag) cpu may now accept maskable hardware interrupts.

  while(1)
  {
    #ifndef GRAPHICSMODE
      desktop.Draw(&rend);
      rend.display(&vga);
    #endif
  } //this is infinite loop , this os currently has nothing to do in this main kernel thread but interrupt can occur Activate function enable them

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

