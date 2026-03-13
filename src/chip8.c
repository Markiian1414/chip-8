#include <stdio.h>
#include <stdlib.h>

#include "chip8.h"

void init_CHIP8(){
	I  = 0;
	PC = START_ADRESS;
	SP = 0;

	memset(memory, 0, sizeof(memory)); // mem reset
	memset(V, 0, sizeof(V)); // registers reset

	delay_timer = 0;
	sound_timer = 0;

	memset(display, 0, sizeof(display));
	memset(stack, 0, sizeof(stack));
	memset(keyboard, 0, sizeof(keyboard));
}		
