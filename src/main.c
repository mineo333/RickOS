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

#define ISR(x) asm volatile ("int %0" : :"g"(x));


extern void load_gdt(struct gdt_ptr_struct* gdt_ptr);
char* heap_brk = &_begin_data;
extern char str;
extern void test_int2();
extern void call_cpuid();
void kernel_init()
{
//	struct idt idt;
	struct gdt_ptr_struct* gdt = (struct gdt_ptr_struct*)malloc(sizeof(struct gdt_ptr_struct));

	monitor_clear();

	setup_gdt(gdt);
	load_gdt(gdt);


	paging_init();



	setup_idt();

	ISR(0) //THIS IS SOME UGLY CODE. idk how do properly do macro expansion but i'll try to learn
	ISR(1)
	ISR(2)
	ISR(3)
	ISR(4)
	ISR(5)
	ISR(6)
	ISR(7)
	ISR(8)
	ISR(9)
	ISR(10)
	ISR(11)
	ISR(12)
	ISR(13)
	ISR(14)
	ISR(15)
	ISR(16)
	ISR(17)
	ISR(18)
	ISR(19)
	ISR(20)
	ISR(21)
	ISR(22)
	ISR(23)
	ISR(24)
	ISR(25)
	ISR(26)
	ISR(27)
	ISR(28)
	ISR(29)
	ISR(30)
	ISR(31)
}
