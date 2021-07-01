CC=i686-elf-gcc
ASMCC=nasm
QEMU= qemu-system-i386
objects= boot.o main.o
IDIR=../include
CFLAGS=-I $(IDIR) -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASMFLAGS= -felf32


all: $(objects)
				$(CC) -T linker.ld -o rickos.bin -ffreestanding -O2 -nostdlib $(objects) -lgcc
main.o:
			$(CC) $(CFLAGS) -c main.c -o main.o
boot.o:
	$(ASMCC) $(ASMFLAGS) boot.s -o boot.o

.PHONY: clean run all

clean: #clean target
	rm rickos.bin $(objects)
run:
	$(QEMU) -kernel rickos.bin
