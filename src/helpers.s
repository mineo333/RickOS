section .text
global load_gdt
load_gdt:
	mov eax, [esp+4]
	lgdt [eax] ;load the gdt
	mov ax, 0x10
	mov ds, ax        ; Load all data segment selectors
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush ;implicitly loads cs
.flush:
	ret

global load_cr3
load_cr3:
mov eax, [esp+4] ; this is the cr3 descriptor;
mov cr3, eax
mov ecx, cr0
or ecx, 0x80000000 ; also enables WP
mov cr0, ecx
ret

global ret_cr0
ret_cr0:
mov eax, cr0
ret
