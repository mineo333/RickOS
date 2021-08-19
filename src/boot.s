; Declare constants for the multiboot header.
MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot


section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM


section .rodata
global str
str: db "Successfully Loaded GDT"


section .data

resb 16384 ; heap. symbols are in the linker script


section .bss
align 16
global stack_bottom
stack_bottom: resb 16384 ; 16 KiB

global stack_top
stack_top: resb 16 ; padding of 16 bytes





global gdt_bottom
gdt_bottom: resb 128

global gdt_top
gdt_top: resb 16 ; padding to 16 bytes


global idt_bottom
idt_bottom: resb 128

global idt_top
idt_top: resb 16 ; padding to 16 bytes


section .pgtable
align 4096

global pg_table_start ;every one of these global variables are 4kb aligned
global pg_table_end
global pg_dir_start
global pg_dir_end
pg_dir_start: resb 8192
pg_dir_end:
pg_table_start:
resb 4210688    ;1028 KiB. We only need 1025 KiB to map 1 GiB but I made it 4 KiB aligned.
pg_table_end:
resb 4096





section .text
global _start:function (_start.end - _start)
_start:



	mov esp, stack_top ; begin stack



	extern kernel_init
	call kernel_init	; this would be a great time to set up the gdt
	


.jmppoint:
jmp _start.jmppoint
.end:
