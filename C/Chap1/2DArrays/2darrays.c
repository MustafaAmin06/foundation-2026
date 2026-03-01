#include <stdio.h>

int main(void) {
  int myArray[6][6];
  
  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 6; col++) {
        if (myArray[row][col] == 1){
            if (col < 4 && myArray[row][col + 1] == 1 && myArray[row][col + 2] == 1){
                printf("found");
            }
        }
    }
  }
  printf("%d", *(myArray[0] + 1));
  return 0;
}