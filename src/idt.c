#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "idt.h"


//for the segment selector because we are working in paging we need only choose the generic kernel selector
void idt_gate(uint32_t base, uint8_t flags, struct idt_entry* idt_entry){
  idt_entry -> base_lo = base & 0xFFFF;
  idt_entry -> base_hi = (base & 0xFFFF0000)>>16;
  idt_entry -> always0 = 0x0;
  idt_entry -> sel = 0x8; //this is kernel code segment. The CPL needs to be changed to ring 0
  idt_entry -> flags = flags;
}


void setup_idt(){
  struct idt_entry* idt_bot = &idt_bottom;
  struct idt idt;
  for(uint32_t i = 0; i<=4; i++, idt_bot++){
    idt_gate((uint32_t)isr0, 0x8E, idt_bot);
  }
  idt.base = (uint32_t)&idt_bottom;
  idt.limit = (32-1)*8;

  load_idt(&idt);

}
