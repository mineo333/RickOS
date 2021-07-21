extern struct gdtdesc gdt_bottom;
extern struct gdtdesc gdt_top;

struct gdtdesc {
    uint16_t lim0_15;
    uint16_t base0_15;
    uint8_t base16_23;
    uint8_t acces;
    uint8_t lim16_19:4;
    uint8_t other:4;
    uint8_t base24_31;
} __attribute__ ((packed));


struct gdt_ptr_struct
{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint32_t base;                // The address of the first gdt_entry_t struct.
}__attribute__((packed));

void gdt_gate(uint32_t base, uint32_t limite, uint8_t acces, uint8_t other, struct gdtdesc *desc);

void setup_gdt(struct gdt_ptr_struct* gdt_ptr);
