#include "LD47.h"

void handleKeyboard(Controller *controller, SDL_Event event) {
    switch(event.key.keysym.sym) {
        case SDLK_SPACE: {
            controller->Accept.pressed = 1;
        }
    }
}

void handleInput(Controller  *controller) {
    SDL_Event event;
    int quit = 0;
    while( SDL_PollEvent( &event ) )
    {
        switch(event.type) {
            case SDL_QUIT: {
                controller->Exit.pressed = 1; 
                break;
            }
            case SDL_KEYDOWN: {
                handleKeyboard(controller, event);
                break;
            }
        }
    }
}

void updateGame(GameState *state) {
    handleInput(state->controller);
    if(state->controller->Exit.pressed)
        state->quit = 1;
    return;
}

void render(GameState *state) {
    return;
}

void freeGameState(GameState *state) {
    SDL_GL_DeleteContext(state->glContext);
    SDL_DestroyWindow(state->window);
}

void gameStateInit(GameState *state) {
    state->initialised = 1;
    state->controller = malloc(sizeof(Controller));
    state->state = malloc(sizeof(PlayState));
    state->quit = 0;
}
