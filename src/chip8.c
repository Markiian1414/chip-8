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

void cycle(){


}