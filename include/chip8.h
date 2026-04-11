#pragma once

#include <stdbool.h>
#include <stdint.h>

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

typedef struct{
	uint8_t memory[4096]; // 4KB(4096 bytes)
	uint8_t V[16]; // 16 REGISTERS
	uint16_t I;
	uint16_t PC; // program counter
	uint16_t opcode; // curr opcode 
	uint8_t SP; //topmost lvl of the stack
	

	uint8_t delay_timer;
	uint8_t sound_timer;

	uint8_t display[SCREEN_WIDTH*SCREEN_HEIGHT]; // screen size(64x32)                              

	uint16_t stack[16];

	uint8_t fontset[80];

	uint8_t keyboard[16];
	bool drawFlag;
} Chip8;

//Func prototypes
void init_CHIP8(Chip8 *c8);
bool loadROM(Chip8 *c8,const char* file);
void fetch(Chip8 *c8);
void execute(Chip8 *c8);

