#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
int main(void) {
  for(int i = 0; i<0x40000000; i+=0x1000){
    if(i % 4096 != 0){
      printf("Wrong");
    }
  }
}
