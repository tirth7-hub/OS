
# run the following commands:
# sudo apt-get install g++ binutils libc6-dev-i386
# sudo apt-get install VirtualBox grub-legacy xorriso

GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = obj/loader.o \
	  obj/gdt.o \
	  obj/memorymanagement.o \
	  obj/drivers/driver.o \
	  obj/hardwarecommunication/port.o \
	  obj/hardwarecommunication/interruptstubs.o \
	  obj/hardwarecommunication/interrupts.o \
	  obj/multitasking.o \
	  obj/drivers/amd_am79c973.o \
	  obj/hardwarecommunication/pci.o \
	  obj/drivers/keyboard.o \
	  obj/drivers/mouse.o\
	  obj/drivers/vga.o\
	  obj/drivers/ata.o\
	  obj/gui/widget.o\
	  obj/gui/window.o\
	  obj/gui/desktop.o\
	  obj/kernel.o



obj/%.o: src/%.cpp   # this part of code help to convert the c++ file into the object(.o) files whicgh is mention in variable ojects
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.s   # this part of code help to convert the loader.s -> loader.o and interruptstube.s -> interruptstubes.o
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

MarkOS.bin: linker.ld $(objects)  #it take all the object file and produce MarkOS.bin using linker.ld
	ld $(LDPARAMS) -T $< -o $@ $(objects)

MarkOS.iso: MarkOS.bin  #create bootable iso file copntain kernel
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp MarkOS.bin iso/boot/MarkOS.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "Mark" {'  		 >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/MarkOS.bin'    >> iso/boot/grub/grub.cfg  # tell GRUB that it is multiboot kernel
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=MarkOS.iso iso
	rm -rf iso

run: MarkOS.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm 'MARKOS' &

install: MarkOS.bin
	sudo cp $< /boot/MarkOS.bin

.PHONY: clean
clean:
	rm -rf obj MarkOS.bin MarkOS.iso



