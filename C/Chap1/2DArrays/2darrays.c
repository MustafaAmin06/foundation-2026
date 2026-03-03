#include <stdio.h>

void calculateRowSums(int rows, int cols, int matrix[rows][cols], int results[rows]);


int main(void) {
  int matrix[6][6];
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      matrix[i][j] = rand() % 100;
    }
  }
}