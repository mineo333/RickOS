#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "gdt.h"

void gdt_gate(uint32_t base, uint32_t limite, uint8_t acces, uint8_t other, struct gdtdesc *desc)
{
    desc->lim0_15 = (limite & 0xffff);
    desc->base0_15 = (base & 0xffff);
    desc->base16_23 = (base & 0xff0000) >> 16;
    desc->acces = acces;
    desc->lim16_19 = (limite & 0xf0000) >> 16;
    desc->other = (other & 0xf);
    desc->base24_31 = (base & 0xff000000) >> 24;
    return;
}

void setup_gdt(struct gdt_ptr_struct* gdt_ptr){




	struct gdtdesc* gdt = gdt_bottom; //each gdtdesc is 8 bytes
	gdt_ptr->limit = (sizeof(struct gdtdesc)*5)-1;
	gdt_ptr-> base = (uint32_t)gdt_bottom;



	gdt_gate(0, 0, 0, 0, gdt); //null gdt gate
	gdt_gate(0, 0xFFFFF, 0x9A, 0x0D, gdt+1); //kernel code segment. This is in page granularity
	gdt_gate(0, 0xFFFFF, 0x92, 0x0D, gdt+2); //kernel data segment
	gdt_gate(0, 0xFFFFF, 0xFA, 0x0D, gdt+3); //user code segment
	gdt_gate(0, 0xFFFFF, 0xF2, 0x0D, gdt+4); //user data segment


}
