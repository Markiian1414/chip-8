#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "chip8.h"

void init_CHIP8(){
	I  = 0;
	PC = 0x200;
	SP = 0;

	memset(memory, 0, sizeof(memory)); // mem reset
	memset(V, 0, sizeof(V)); // registers reset

	delay_timer = 0;
	sound_timer = 0;

	memset(display, 0, sizeof(display));
	memset(stack, 0, sizeof(stack));
	memset(keyboard, 0, sizeof(keyboard));
	memcpy(memory, fontset, sizeof(uint8_t)*80);
}		

bool loadROM(char* file){
	FILE* f = fopen(file, "rb");
	// Check file existence
	if (f == NULL){
		printf("File doesn't exist.\n");
		return false;
	}
	
	//Size of file (byte)
	fseek(f, 0, SEEK_END);
	long size_of_file = ftell(f);	
	rewind(f);

	//Allowable file size
	if(size_of_file > sizeof(memory) - 512){
		printf("ROM too large.\n");
		fclose(f);
		return false;
	}

	fread(&memory[512], sizeof(uint8_t), size_of_file, f);

	fclose(f);
	return true;	
}

void fetch(){
	opcode = memory[PC] << 8 | memory[PC + 1];
	PC += 2;
}

void execute(){
	switch (opcode & 0xF000)
	{
	case 0x0000: // 00E0
		memset(display, 0, sizeof(display));
		break;
	
	case 0x1000: // 1NNN
		PC = opcode & 0x0FFF;
		break;
	
	case 0x2000: // 2NNN

		break;
	case 0x3000: // 3XKK

		break;
	case 0x4000: // 4XKK

		break;
	
	case 0x5000: // 5XY0

		break;
	case 0x6000: // 6XKK
		V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
		break;
	case 0x7000: // 7XKK
		V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
		break;
	
	case 0x8000: // 8XY_

		break;
	case 0x9000: // 9XY0

		break;
	
	case 0xA000: // ANNN
		I = opcode & 0x0FFF;
		break;
	
	case 0xB000: // BNNN

		break;
	case 0xC000: // CXKK

		break;
	case 0xD000: // DXYN
		
		break;
	
	case 0xE000: // EX__

		break;
	case 0xF000: // FX__

		break;
	
	default:
		break;
	}
}