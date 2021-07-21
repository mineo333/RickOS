#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "stdlib.h"
#include "gdt.h"
#include "page.h"
#include "idt.h"
#include "monitor.h"
#include "common.h"
//THIS NEEDS TO BE COMPILED WITH A ix86 compiler
//extern void setup_gdt();


extern void load_gdt(struct gdt_ptr_struct* gdt_ptr);
char* heap_brk = &_begin_data;
extern char str;
extern void _start(); //the beginning of the text section
extern uint32_t ret_cr0();
struct gdt_ptr_struct* setup_gdt(){



	struct gdt_ptr_struct* gdt_ptr = (struct gdt_ptr_struct*)malloc(sizeof(struct gdt_ptr_struct));
	struct gdtdesc* gdt = &gdt_bottom; //each gdtdesc is 8 bytes
	gdt_ptr->limit = (sizeof(struct gdtdesc)*5)-1;
	gdt_ptr-> base = (uint32_t)&gdt_bottom;



	gdt_gate(0, 0, 0, 0, gdt); //null gdt gate
	gdt_gate(0, 0xFFFFF, 0x9A, 0x0D, gdt+1); //kernel code segment. This is in page granularity
	gdt_gate(0, 0xFFFFF, 0x92, 0x0D, gdt+2); //kernel data segment
	gdt_gate(0, 0xFFFFF, 0xFA, 0x0D, gdt+3); //user code segment
	gdt_gate(0, 0xFFFFF, 0xF2, 0x0D, gdt+4); //user data segment

	return gdt_ptr;

}
void isr_handler(struct registers_t regs){
	monitor_write("recieved interrupt: ");
	monitor_write_dec(regs.int_no);
	monitor_put('\n');

}


void kernel_init()
{
	struct idt idt;


	monitor_clear();

	struct gdt_ptr_struct* gdt_ptr = setup_gdt();
	load_gdt(gdt_ptr);
	paging_init();
	setup_idt();
	asm volatile ("sidt %0" : "=m"(idt));
	monitor_write_dec(idt.base);
	monitor_put('\n');
	monitor_write_dec(idt.limit);
	monitor_put('\n');
//	asm volatile ("int $0x3");

}
