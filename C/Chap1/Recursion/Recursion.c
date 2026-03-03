#include <stdio.h>

int main(void) {
    // Top part of 9 (closed circle)
    for(int i = 0; i < 3; i++){
        printf("*****\n");
        printf("*   *\n");
    }
    
    // Bottom connection
    printf("*****\n");
    
    // Descending tail
    for(int i = 0; i < 4; i++){
        printf("    *\n");
    }
    
    return 0;
}