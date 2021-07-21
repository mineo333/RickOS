#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>



// The VGA framebuffer starts at 0xB8000.


void move_cursor();

void scroll();

void monitor_clear();

void monitor_put(char c);

void monitor_write(char *c);

void monitor_write_dec(uint32_t num);
