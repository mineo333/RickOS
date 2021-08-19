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

global test_int2
test_int2:
mov eax, 0x28
mov fs, eax
ret

global call_cpuid
call_cpuid:
push ebx ;ebx is callee saved according to the SysV calling ABI. CPUID modifies ebx.
mov esi, [esp+8] ; contrary to EBX, ESI is caller-saved and thus does not need to be saved on the stack. 
mov eax, 1 ;this will make cpuid execute the way we want to
cpuid ;the values of cpuid will be placed in ecx and edx

mov [esi], ecx
mov [esi+4], edx
pop ebx
ret
