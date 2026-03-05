#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

typedef struct chip8{
    uint8_t memory[4096]; // main memory, 0x000 -> 0x1FF stores fonts, 0x200 -> 2xFFF stores ROM
    uint16_t stack[16]; // Essentially a record book of all the subroutines (functions) the cpu does
    uint16_t I; // This stores mem addresses. 16bits because 8bits is too small for 12 bits of mem we have
    uint16_t pc; // Holds the address of the next instruction to be executed
    uint8_t V[16]; // General purpose registers. Do math here
    uint8_t sp; // An index for the stack
    uint8_t delaytimer;  // Both of these are simple clocks
    uint8_t soundtimer;
} chip8;

int main(){
}

void powerOn(chip8 emulator){

}