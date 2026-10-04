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


