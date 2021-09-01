#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "idt.h"
#include "monitor.h"

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
  uint16_t limit = (sizeof(struct idt_entry)*32)-1;
  uint32_t base = (uint32_t)&idt_bottom;
  struct idt idt;





  idt_gate((uint32_t)isr0, 0x8E,idt_bot);
  idt_gate((uint32_t)isr1, 0x8E,idt_bot+1);
  idt_gate((uint32_t)isr2, 0x8E,idt_bot+2);
  idt_gate((uint32_t)isr3, 0x8E,idt_bot+3);
  idt_gate((uint32_t)isr4, 0x8E,idt_bot+4);
  idt_gate((uint32_t)isr5, 0x8E,idt_bot+5);
  idt_gate((uint32_t)isr6, 0x8E,idt_bot+6);
  idt_gate((uint32_t)isr7, 0x8E,idt_bot+7);
  idt_gate((uint32_t)isr8, 0x8E,idt_bot+8);
  idt_gate((uint32_t)isr9, 0x8E,idt_bot+9);
  idt_gate((uint32_t)isr10, 0x8E,idt_bot+10);
  idt_gate((uint32_t)isr11, 0x8E,idt_bot+11);
  idt_gate((uint32_t)isr12, 0x8E,idt_bot+12);
  idt_gate((uint32_t)isr13, 0x8E,idt_bot+13);
  idt_gate((uint32_t)isr14, 0x8E,idt_bot+14);
  idt_gate((uint32_t)isr15, 0x8E,idt_bot+15);
  idt_gate((uint32_t)isr16, 0x8E,idt_bot+16);
  idt_gate((uint32_t)isr17, 0x8E,idt_bot+17);
  idt_gate((uint32_t)isr18, 0x8E,idt_bot+18);
  idt_gate((uint32_t)isr19, 0x8E,idt_bot+19);
  idt_gate((uint32_t)isr20, 0x8E,idt_bot+20);
  idt_gate((uint32_t)isr21, 0x8E,idt_bot+21);
  idt_gate((uint32_t)isr22, 0x8E,idt_bot+22);
  idt_gate((uint32_t)isr23, 0x8E,idt_bot+23);
  idt_gate((uint32_t)isr24, 0x8E,idt_bot+24);
  idt_gate((uint32_t)isr25, 0x8E,idt_bot+25);
  idt_gate((uint32_t)isr26, 0x8E,idt_bot+26);
  idt_gate((uint32_t)isr27, 0x8E,idt_bot+27);
  idt_gate((uint32_t)isr28, 0x8E,idt_bot+28);
  idt_gate((uint32_t)isr29, 0x8E,idt_bot+29);
  idt_gate((uint32_t)isr30, 0x8E,idt_bot+30);
  idt_gate((uint32_t)isr31, 0x8E,idt_bot+31);


  idt.limit = limit;
  idt.base = base;
  //idt.base = base;
  //idt.limit = limit;
  load_idt(&idt);

}

void isr_handler(struct registers_t* regs){
	monitor_write("recieved interrupt: ");
  monitor_write_dec(regs->int_no);
  monitor_put('\n');

}
