# OS
Make my first Operating system name from scratch
building a 32-bit x86 kernel


Computer starts
				     ↓
				BIOS/firmware
				     ↓
				GRUB
				     ↓
				loader.s
				     ↓
				Create stack
				     ↓
				callConstructors()
				     ↓
				kernelMain()
				     ↓
				printf("Hello...")
				     ↓
				Create GDT
				     ↓
				Create InterruptManager
				     ↓
				Create KeyboardDriver
				     ↓
				Enable CPU interrupts
				     ↓
				User presses a key
				     ↓
				Keyboard hardware
				     ↓
				PIC
				     ↓
				CPU interrupt
				     ↓
				IDT
				     ↓
				interruptstube.s
				     ↓
				InterruptManager::HandleInterrupt()
				     ↓
				KeyboardDriver::HandleInterrupt()
				     ↓
				Read keyboard port
				     ↓
				printf()
				     ↓
				Character appears on screen

#ifndef __TYPES_H
#define __TYPES_H       It prevents the contents of types.h from being included multiple times in the same compilation unit. 



keyboard route
steo-1 : press a key (A)
step-2 : for key (A)-0x1E
step-3 : the controller places the scan code where the cpu can read it through (I/o   		 port 0x60)
step-4 : the keyboard generates: IRQ1
step-5 : the pic maps irq1 to -> 0x20 + 1,  0x21
		 inetrruptDescripterTable[0x21]
		 entry points -> HandleInterruptRequest0x01
step-6 : pusha, pushl and all register -> save the cpu state
step-7 : call -> InterruptManager::HandleInterrupt(0x21, esp)
step-8 : Active manager calls-> DoHandleInterrupt(0x21, esp)


Keyboard.cpp -> keuboard.h -> interrupts.h + port.h

kernel.cpp 
	|--gdt.h
	|--interupts.h
	|--keyboard.h
	
	
	
	

		 





