#include <stdio.h>
#include "LD47.h"
#include "SDL2/SDL.h"
#include "opengl.h"
#include <GL/gl.h>

int initOpenGL() {
    mat4 projection = OrthProjection(16/9, 0.1, 1000.0);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((float *) &projection);
    vec3 position = {0.0, 10.0, 5};
    mat4 cam = Camera(position);
    glMatrixMode(GL_MODELVIEW);
    glLoadTransposeMatrixf((float *) &cam);
    return 0;
}

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
    initOpenGL();
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
