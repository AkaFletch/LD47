#include <stdio.h>
#include "LD47.h"
#include "SDL2/SDL.h"


int sdlRunner()
{
    GameState state = {};
    SDL_Init(SDL_INIT_EVERYTHING);
    state.window = SDL_CreateWindow("LD47", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED); 
    gameStateInit(&state);
    while(!state.quit) {
        updateGame(&state);
        render(&state);
    }
    freeGameState(&state);
    SDL_Quit();
    return 0;
}

int main(int argc, char* argv[]) {
    printf("Started\n");
    return sdlRunner();
}
