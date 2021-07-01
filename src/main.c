#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "stdlib.h"
#include "tty.h"
#include "gdt.h"
#include "page.h"
//THIS NEEDS TO BE COMPILED WITH A ix86 compiler
//extern void setup_gdt();
extern void load_gdt(struct gdt_ptr_struct* gdt_ptr);
char* heap_brk = &_begin_data;
extern char str;
extern void _start(); //the beginning of the text section
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

void kernel_init()
{
	terminal_initialize();
	struct gdt_ptr_struct* gdt_ptr = setup_gdt();



	load_gdt(gdt_ptr);
	if((uint32_t)&pg_table_start % 4096 == 0 && (uint32_t)&pg_table_end % 4096 == 0 && (uint32_t)&pg_dir_start % 4096 == 0 && (uint32_t)&pg_dir_end % 4096 == 0){
		terminal_writestring(&str);
	}

}




/*char* gdt_base_str1 = (char*)malloc(12);
char* gdt_base_str2 = (char*)malloc(12);
itoa((uint32_t)&heap_brk, gdt_base_str1, 10); //forgot the fucking pointer symbol.

terminal_writestringln("Writing address pre-malloc:");
terminal_writestringln(gdt_base_str1);

itoa((uint32_t)&heap_brk, gdt_base_str2, 10); //forgot the fucking pointer symbol.

terminal_writestringln("Writing address post-malloc (12 bytes):");
terminal_writestringln(gdt_base_str2);*/
