#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
/* this literally only has itoa for debugging reasons*/
extern char _begin_data;
extern char _end_data;
extern char* heap_brk; //eventually going to need to throw this into some kind of task struct. Each program should have a heap_brk

void outb(uint16_t port, uint8_t value);

uint16_t inb(uint16_t port);

uint16_t inw(uint16_t port);

void swap(char* first, char* second);

void reverse(char* str, uint32_t length);

char* itoa(uint32_t num, char* str, uint32_t base);

void* malloc(uint32_t buf_size);

void free(void* ptr);
