#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "stdlib.h"
#include "pic.h"
#include "monitor.h"
//this code is the init and management code for the 8259 PIC.
void setup_pic(){
  uint8_t m1;
  uint8_t m2;
  m1 = inb(PIC1_DATA);                        // save masks
	monitor_write_dec(m1);

  

}
