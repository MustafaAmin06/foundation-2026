#include <stdio.h>

int main(void) {
  printf("Enter characters: \n");
  char c = getchar();
  while (c != '\n') {
    printf("%c\n", c);
    c = getchar();
  }
  return 0;
}