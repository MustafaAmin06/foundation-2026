#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void calculateRowSums(int rows, int cols, int matrix[rows][cols], int results[rows]);
bool initSectionInArray(int A[1000][1000], int result[1000][1000], int rows, int cols, int sr, int er, int sc, int ec, int value);

int main(void) {
  // Allocate arrays dynamically since 1000x1000 is large
  int (*A)[1000] = malloc(1000 * sizeof(int[1000]));
  int (*result)[1000] = malloc(1000 * sizeof(int[1000]));
  
  // Initialize input array A with values (0-99)
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      A[i][j] = (i + j) % 100;
    }
  }
  
  // Test: Set a 50x50 section (rows 10-59, cols 10-59) to value 255
  int sr = 10, er = 59, sc = 10, ec = 59;
  int value = 255;
  
  bool success = initSectionInArray(A, result, 0, 0, sr, er, sc, ec, value);
  
  if (success) {
    printf("Function executed successfully!\n");
    
    // Print a sample of the result to verify
    printf("\nSample output (rows 5-65, cols 5-65):\n");
    for (int r = 5; r <= 65; r += 10) {
      for (int c = 5; c <= 65; c += 10) {
        printf("result[%d][%d] = %d  ", r, c, result[r][c]);
      }
      printf("\n");
    }
    
    // Verify the section was properly set
    printf("\nVerification:\n");
    printf("result[15][15] (inside section): %d (should be %d)\n", result[15][15], value);
    printf("result[5][5] (outside section): %d (should be %d)\n", result[5][5], A[5][5]);
    printf("result[65][65] (outside section): %d (should be %d)\n", result[65][65], A[65][65]);
  } else {
    printf("Function returned false!\n");
  }
  
  // Free allocated memory
  free(A);
  free(result);
  
  return 0;
}

void calculateRowSums(int row, int col, int matrix[row][col], int results[row]){
  int sum = 0;
  for(int rows = 0; rows < row; rows++){
    for(int cols = 0; cols < col; cols++){
      sum += matrix[rows][cols];
    }
    results[rows] = sum;
    sum = 0;
  }
}

void transposeMatrix(int rows, int cols, int matrix[rows][cols], int result[cols][rows]) {
    for(int r = 0; r < rows; r++){
      for (int c = 0; c < cols; c++){
        result[c][r] = matrix[r][c];
      }
    }
}

void multiplyMatrices(int r1, int c1, int A[r1][c1], int r2, int c2, int B[r2][c2], int result[r1][c2]) {

  for(int r = 0; r < r1; r++){
    for(int c = 0; c < c2; c++){
      int sum = 0;
      for(int k = 0; k < c1; k++){
        sum += A[r][c + k] * B[c + k][r];
      }
      result[r][c] = sum;
    }
  }
}

//  The function modifies the elements of a 1000x1000 integer 2-dimensional array A 
// to a specified value within the rectangular boundaries defined by the parameters 
// Start, rowEnd, colStart, and colEnd.

bool initSectionInArray(int A[1000][1000], int result[1000][1000], int rows, int cols, int sr, int er, int sc, int ec, int value){
  if((rows < 0 || rows > 1000) || (cols < 0 || cols > 1000)){
    return false;
  }
  for(int r = rows; r < 1000; r++){
    for(int c = cols; c < 1000; c++){
      if((r >= sr && r <= er) && (c >= sc && c<=ec)){
        result[r][c] = value;
      } else {
        result[r][c] = A[r][c];
      }
    }
  }
  return true;
}