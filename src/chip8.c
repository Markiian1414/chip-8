#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "chip8.h"


void init_CHIP8(Chip8 *c8){
	c8->I  = 0;
	c8->PC = 0x200;
	c8->SP = 0;

	memset(c8->memory, 0, sizeof(c8->memory)); // mem reset
	memset(c8->V, 0, sizeof(c8->V)); // registers reset

	c8->delay_timer = 0;
	c8->sound_timer = 0;
	c8->drawFlag = false;

	memset(c8->display, 0, sizeof(c8->display));
	memset(c8->stack, 0, sizeof(c8->stack));
	memset(c8->keyboard, 0, sizeof(c8->keyboard));
	
	uint8_t fontset_data [80]=
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};
	memcpy(c8->fontset, fontset_data, sizeof(uint8_t)*80);
	memcpy(c8->memory, c8->fontset, sizeof(uint8_t)*80);
}		

bool loadROM(Chip8 *c8, const char* file){
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
	if(size_of_file > sizeof(c8->memory) - 512){
		printf("ROM too large.\n");
		fclose(f);
		return false;
	}

	fread(&c8->memory[512], sizeof(uint8_t), size_of_file, f);

	fclose(f);
	return true;	
}

void fetch(Chip8 *c8){
	c8->opcode = c8->memory[c8->PC] << 8 | c8->memory[c8->PC + 1];
	c8->PC += 2;
}

void execute(Chip8 *c8){
	switch (c8->opcode & 0xF000)
	{
	case 0x0000: // 00E0
		switch(c8->opcode & 0x00FF)
    	{
			case 0x00E0:
				memset(c8->display, 0, sizeof(c8->display));
				c8->drawFlag = true;
				break;

			case 0x00EE:
				c8->SP--;
				c8->PC = c8->stack[c8->SP];
				break;
    	}
    	break;
	
	case 0x1000: // 1NNN
		c8->PC = c8->opcode & 0x0FFF;
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
		c8->V[(c8->opcode & 0x0F00) >> 8] = c8->opcode & 0x00FF;
		break;
	case 0x7000: // 7XKK
		c8->V[(c8->opcode & 0x0F00) >> 8] += c8->opcode & 0x00FF;
		break;
	
	case 0x8000: // 8XY_

		break;
	case 0x9000: // 9XY0

		break;
	
	case 0xA000: // ANNN
		c8->I = c8->opcode & 0x0FFF;
		break;
	
	case 0xB000: // BNNN

		break;
	case 0xC000: // CXKK

		break;
	case 0xD000: // DXYN
		uint16_t x = c8->V[(c8->opcode & 0x0F00) >> 8];
		uint16_t y = c8->V[(c8->opcode & 0x00F0) >> 4];
		uint16_t height = (c8->opcode & 0x000F);
		uint8_t pixel;
		c8->V[15] = 0; // VF Register (last in V[16])

		for(int i=0; i<height; i++)
		{
			pixel = c8->memory[c8->I + i];
			for (int j=0; j<8; j++)
			{
				if ((pixel & (0x80 >> j)) != 0)
				{	
					if (c8->display[((y+i)*64+(x+j))] == 1)
					{
						c8->V[15] = 1;
 					}
					c8->display[((y+i)*64+(x+j))] ^= 1;
				}
				
			}
		}
		
		c8->drawFlag = true;
		break;
	
	case 0xE000: // EX__
		switch (c8->opcode & 0x00FF)
		{
		case 0x009E:
			if(c8->keyboard[c8->V[(c8->opcode & 0x0F00) >> 8]] != 0)
			{
				c8->PC += 2;
			}
			break;
		case 0x00A1:
			if(c8->keyboard[c8->V[(c8->opcode & 0x0F00) >> 8]] == 0)
			{
				c8->PC += 2;
			}
			break;
		}
		break;
	case 0xF000: // FX__
		switch (c8->opcode & 0x00FF)
		{
		case 0x0007:
			c8->V[(c8->opcode & 0x0F00) >> 8] = c8->delay_timer;
			break;
		
		case 0x0015:
			c8->delay_timer = c8->V[(c8->opcode & 0x0F00) >> 8];
			break;
		}
		break;
	}
}