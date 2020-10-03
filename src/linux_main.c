#include <stdio.h>
#include "LD47.h"
#include "SDL2/SDL.h"
#include "opengl.h"
#include <GL/gl.h>

int sdlRunner()
{
    GameState state = {};
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    state.window = SDL_CreateWindow("LD47", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920/2, 1080/2, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(!state.window) {
        printf("Failed to initialise window\n");
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(state.window);
    if(!context) {
        printf("Failed to create opengl context");
        return -1;
    }

    SDL_GL_SetSwapInterval(1);

    gameStateInit(&state);
    while(!state.quit) {
        updateGame(&state);
        render(&state);

        SDL_GL_SwapWindow(state.window);
    }

    freeGameState(&state);

    SDL_Quit();
    return 0;
}

int main(int argc, char* argv[]) {
    printf("Started\n");
    return sdlRunner();
}
