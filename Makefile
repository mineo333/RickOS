CC=i686-elf-gcc
ASMCC=nasm
QEMU= qemu-system-i386
IDIR=include
BINDIR = bin
TARGETDIR = .
SRCDIR = src
objects = boot.o helpers.o interrupt.o page.o stdlib.o monitor.o idt.o main.o gdt.o
CFLAGS=-I $(IDIR) -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASMFLAGS= -felf32




rickos.bin: $(objects)
	$(CC) -T linker.ld -o $(TARGETDIR)/$@ -ffreestanding -O2 -nostdlib $(patsubst %.o, $(BINDIR)/%.o, $^) -lgcc

%.o: $(SRCDIR)/%.c #C recipe
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ -c $<
%.o: $(SRCDIR)/%.s #NASM recipe
	$(ASMCC) $(ASMFLAGS) -o $(BINDIR)/$@ $<


.PHONY: clean run gdb all remake

all:
	mkdir $(BINDIR)
	rickos.bin
remake:
	clean all
clean: #clean target
	rm $(TARGETDIR)/rickos.bin $(patsubst %.o, $(BINDIR)/%.o, $(objects))
run:
	$(QEMU) -kernel $(TARGETDIR)/rickos.bin
gdb:
	$(QEMU) -s -S -kernel $(TARGETDIR)/rickos.bin
