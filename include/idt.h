extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();

#define GETISR(i) isr##i();
struct idt_entry
{
   uint16_t base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
   uint16_t sel;                 // Kernel segment selector.
   uint8_t  always0;             // This must always be zero.
   uint8_t  flags;               // More flags. See documentation.
   uint16_t base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));

struct idt {
    uint32_t base;
    uint16_t limit;
}__attribute__((packed));


extern struct idt_entry idt_bottom;
extern void load_idt(struct idt* idt);



struct registers_t
{
   uint32_t ds;                  // Data segment selector
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
   uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} __attribute__((packed));

void idt_gate(uint32_t base, uint8_t flags, struct idt_entry* idt_entry);

void setup_idt();

void isr_handler(struct registers_t regs);
