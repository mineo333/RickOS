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

	//monitor_write("Hello World");
	//call_cpuid();
	setup_idt();
//	monitor_clear();
	//asm volatile ("sidt %0" : "=m"(idt));
/*	monitor_write_dec(idt.base);
	monitor_put('\n');
	monitor_write_dec(idt.limit);
	monitor_put('\n');*/

	//test_int2();


}
