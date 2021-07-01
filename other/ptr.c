#include <stdio.h>

int main(void) {
  int  var[] = {10, 100, 200};
  char* ptr = (char*)&var[2];
  printf("%d", *(ptr));
  return 0;
}
