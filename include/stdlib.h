#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
/* this literally only has itoa for debugging reasons*/
extern char _begin_data;
extern char _end_data;
extern char* heap_brk; //eventually going to need to throw this into some kind of task struct. Each program should have a heap_brk
void swap(char* first, char* second){
  char temp = *first;
  *first = *second;
  *second = temp;
}

void reverse(char* str, uint32_t length)
{
    uint32_t start = 0;
    uint32_t end = length -1;
    while (start < end)
    {
        swap(str+start, str+end);
        start++;
        end--;
    }
}


// Implementation of itoa()
char* itoa(uint32_t num, char* str, uint32_t base) //there is no support for negative numbers as of right now
{
    uint32_t i = 0;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'


    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}
void* malloc(uint32_t buf_size){ //malloc is most complete for now.

  void* ret;
  if(heap_brk + buf_size + 4> &_end_data){ //no overflow pog. We need the 4 extra bytes for metadata
    return NULL;
  }
  //  terminal_writestringln("Made it past the overflow check");
  *(uint32_t*)heap_brk = buf_size;

  ret = (void*)(heap_brk+4);
  heap_brk += (buf_size+4);
  return ret;
}

void free(void* ptr){
  int buf_size;
  char* begin = (char*)ptr - 4; //first 4 bytes are reserved
  buf_size = *(uint32_t*)(begin); //real cursed shit
  for(char* i = begin; i<begin+buf_size+4; i++){
    *i = (char)0; //zero byte
  }
}
