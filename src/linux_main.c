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
        printf("Failed to create opengl context\n");
        return -1;
    }

    SDL_GL_SetSwapInterval(1);

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        printf("Failed to open mixer audio\n");
        return -1;    
    }
    gameStateInit(&state);
    if(!state.music) {
        printf("Failed to load music file\n");
        return -1;
    }
    float currentTime;
    float delta;
    while(!state.quit) {
        currentTime = SDL_GetTicks();
        updateGame(&state, delta);
        render(&state);
        SDL_GL_SwapWindow(state.window);
        delta = (SDL_GetTicks() - currentTime)/10;
    }

    freeGameState(&state);
    SDL_Quit();
    return 0;
}

int main(int argc, char* argv[]) {
    printf("Started\n");
    return sdlRunner();
}
