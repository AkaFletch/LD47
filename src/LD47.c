#include "LD47.h"

void handleKeyboard(Controller *controller, SDL_Event event) {
    printf("Keypressed\n");
    switch(event.key.keysym.sym) {
        case SDLK_SPACE: {
            controller->Accept.pressed = 1;
            printf("space\n");
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
    SDL_RenderClear(state->renderer); 
    SDL_Rect rect = {0,0, 1920, 1080};
    SDL_Rect rect2 = {100,100, 1920, 1080};
    SDL_SetRenderDrawColor(state->renderer, 255, 155, 255, 0);
    SDL_RenderFillRect(state->renderer, &rect); 
    SDL_SetRenderDrawColor(state->renderer, 255, 0, 0, 0);
    SDL_RenderFillRect(state->renderer, &rect2); 
    SDL_RenderPresent(state->renderer); 
    return;
}

void freeGameState(GameState *state) {
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
}

void gameStateInit(GameState *state) {
    state->initialised = 1;
    state->controller = malloc(sizeof(Controller));
    state->state = malloc(sizeof(PlayState));
    state->quit = 0;
}
