#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


#include "chip8.h"


int main(int argc, char **argv){ //argument count; argument vector
    
    if (argc < 2){
        printf("Error. ");
        return 1;
    }

    //Initialize of CHIP8 and load ROM into memory
    init_CHIP8();
    if(!loadROM(argv[1]))
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

            if(event.type == SDL_KEYDOWN || SDL_KEYUP){
                int pressed = (event.type == SDL_KEYDOWN) ? 1 : 0;
                
                switch (event.key.keysym.sym)
                {
                    case SDLK_1:
                        keyboard[1]=pressed;
                        break;
                    case SDLK_2:
                        keyboard[2]=pressed;
                        break;
                    case SDLK_3:
                        keyboard[3]=pressed;
                        break;
                    case SDLK_4:
                        keyboard[0xC]=pressed;
                        break;
                    case SDLK_q:
                        keyboard[4]=pressed;
                        break;
                    case SDLK_w:
                        keyboard[5]=pressed;
                        break;
                    case SDLK_e:
                        keyboard[6]=pressed;
                        break;
                    case SDLK_r:
                        keyboard[0xD]=pressed;
                        break;
                    case SDLK_a:
                        keyboard[7]=pressed;
                        break;
                    case SDLK_s:
                        keyboard[8]=pressed;
                        break;
                    case SDLK_d:
                        keyboard[9]=pressed;
                        break;
                    case SDLK_f:
                        keyboard[0xF]=pressed;
                        break;
                    case SDLK_z:
                        keyboard[0xA]=pressed;
                        break;
                    case SDLK_x:
                        keyboard[0x0]=pressed;
                        break;
                    case SDLK_c:
                        keyboard[0xB]=pressed;
                        break;
                    case SDLK_v:
                        keyboard[0xF]=pressed;
                        break;
                }
            }    
        }
    

    fetch();
    execute();

    if(drawFlag) {
            SDL_SetRenderDrawColor(renderer, 0,0,0,255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
            for(int y=0; y<SCREEN_HEIGHT; y++) {
                for(int x=0; x<SCREEN_WIDTH; x++) {
                    if(display[y*SCREEN_WIDTH + x]) {
                        SDL_Rect pixel = {x*10, y*10,
                                          10, 10};
                        SDL_RenderFillRect(renderer, &pixel);
                    }
                }
            }

            SDL_RenderPresent(renderer);
            drawFlag = false;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
