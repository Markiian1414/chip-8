#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


#include "chip8.h"


int main(int argc, char **argv){ //argument count; argument vector
    
    Chip8 c8;

    if (argc < 2){
        printf("Error. ");
        return 1;
    }

    //Initialize of CHIP8 and load ROM into memory
    init_CHIP8(&c8);
    if(!loadROM(&c8, argv[1]))
    {
        return 1;
    }

    //SDL initialization
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "SDLInit failed: %s\n", SDL_GetError());

        return 1;
    }

    SDL_Window* window = SDL_CreateWindow ("Chip-8", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        640, 320, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 
        -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    SDL_Event event;

    int running = 1;

    while(running){
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) running = 0;

            if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP){
                int pressed = (event.type == SDL_KEYDOWN) ? 1 : 0;
                
                switch (event.key.keysym.sym)
                {
                    case SDLK_1:
                        c8.keyboard[0x1]=pressed;
                        break;
                    case SDLK_2:
                        c8.keyboard[0x2]=pressed;
                        break;
                    case SDLK_3:
                        c8.keyboard[0x3]=pressed;
                        break;
                    case SDLK_4:
                        c8.keyboard[0xC]=pressed;
                        break;
                    case SDLK_q:
                        c8.keyboard[0x4]=pressed;
                        break;
                    case SDLK_w:
                        c8.keyboard[0x5]=pressed;
                        break;
                    case SDLK_e:
                        c8.keyboard[0x6]=pressed;
                        break;
                    case SDLK_r:
                        c8.keyboard[0xD]=pressed;
                        break;
                    case SDLK_a:
                        c8.keyboard[0x7]=pressed;
                        break;
                    case SDLK_s:
                        c8.keyboard[0x8]=pressed;
                        break;
                    case SDLK_d:
                        c8.keyboard[0x9]=pressed;
                        break;
                    case SDLK_f:
                        c8.keyboard[0xE]=pressed;
                        break;
                    case SDLK_z:
                        c8.keyboard[0xA]=pressed;
                        break;
                    case SDLK_x:
                        c8.keyboard[0x0]=pressed;
                        break;
                    case SDLK_c:
                        c8.keyboard[0xB]=pressed;
                        break;
                    case SDLK_v:
                        c8.keyboard[0xF]=pressed;
                        break;
                }
            }    
        }
    

    for(int i = 0; i < 10; i++) {
        fetch(&c8);
        execute(&c8);
    }

    if(c8.drawFlag) {
            SDL_SetRenderDrawColor(renderer, 0,0,0,255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
            for(int y=0; y<SCREEN_HEIGHT; y++) {
                for(int x=0; x<SCREEN_WIDTH; x++) {
                    if(c8.display[y*SCREEN_WIDTH + x]) {
                        SDL_Rect pixel = {x*10, y*10,
                                          10, 10};
                        SDL_RenderFillRect(renderer, &pixel);
                    }
                }
            }

            SDL_RenderPresent(renderer);
            c8.drawFlag = false;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
