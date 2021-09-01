%macro ISR_NOERRCODE 1  ; define a macro, taking one parameter
  [GLOBAL isr%1]        ; %1 accesses the first parameter.
  isr%1:
  ; As of right now the stack is as follows: (Volume 3 Intel)
  ;_____________ HIGHMEM
  ;SS
  ;ESP pre-int
  ;EFLAGS
  ;CS
  ;EIP <- ESP
  ;_____________ LOWMEM

    push byte 0
    push byte %1 ;push the error code
    jmp isr_common_stub

%endmacro

%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
  ; As of right now the stack is as follows: (Volume 3 Intel)
  ;_____________ HIGHMEM
  ;SS
  ;ESP pre-int
  ;EFLAGS
  ;CS
  ;EIP
  ;Error Code <- ESP
  ;_____________ LOWMEM

    push byte %1 ;push the int code
    jmp isr_common_stub

%endmacro

section .text:
extern isr_handler
isr_common_stub:
   pushad                   ; Pushes EAX, ECX, EDX, EBX, EBP, ESP (original value), EBP, ESI, and EDI (Pushed in that order)

   mov eax, ds               ; Lower 16-bits of eax = ds.
   push eax                 ; save the data segment descriptor
   push esp
   mov eax, 0x10  ; load the kernel data segment descriptor. Everything needs to be eax or that causes problems because it preserves the upper 16 bits of eax which is no bueno
   mov ds, eax
   mov es, eax
   mov fs, eax
   mov gs, eax


   call isr_handler
   add esp, 4
   pop eax
   ;mov eax, 0x10        ; reload the original data segment descriptor. This causes a jump to isr13. Idk why
   mov ds, eax
   mov es, eax
   mov fs, eax
   mov gs, eax

   popad                    ; Pops edi,esi,ebp...
   add esp, 8     ; Cleans up the pushed error code and pushed ISR number
   iret ;pops everything that the CPU put on the stack

   ISR_NOERRCODE 0
   ISR_NOERRCODE 1
   ISR_NOERRCODE 2
   ISR_NOERRCODE 3
   ISR_NOERRCODE 4
   ISR_NOERRCODE 5
   ISR_NOERRCODE 6
   ISR_NOERRCODE 7
   ISR_NOERRCODE 8 ; 8 has no error code. that was a fucking lie. 
   ISR_NOERRCODE 9
   ISR_ERRCODE    10
   ISR_ERRCODE    11
   ISR_ERRCODE    12
   ISR_ERRCODE    13
   ISR_ERRCODE    14
   ISR_NOERRCODE 15
   ISR_NOERRCODE 16
   ISR_ERRCODE    17
   ISR_NOERRCODE 18
   ISR_NOERRCODE 19
   ISR_NOERRCODE 20
   ISR_ERRCODE 21
   ISR_NOERRCODE 22
   ISR_NOERRCODE 23
   ISR_NOERRCODE 24
   ISR_NOERRCODE 25
   ISR_NOERRCODE 26
   ISR_NOERRCODE 27
   ISR_NOERRCODE 28
   ISR_NOERRCODE 29
   ISR_ERRCODE    30
   ISR_NOERRCODE 31
global load_idt
load_idt:
  mov eax, [esp+4]
  lidt [eax]
  sti
  ret
