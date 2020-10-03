#include "LD47.h"

void handleKeyboard(Controller *controller, SDL_Event event) {
    switch(event.key.keysym.sym) {
        case SDLK_SPACE: {
            controller->Accept.pressed = 1;
            break;
        }
    }
}

void handleInput(GameState *state, Controller  *controller) {
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

            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    state->width  = (int) event.window.data1;
                    state->height = (int) event.window.data2;
                }
                break;
            }
        }
    }
}

void updateGame(GameState *state) {
    handleInput(state, state->controller);
    if(state->controller->Exit.pressed)
        state->quit = 1;

    return;
}

void render(GameState *state) {
    glViewport(0, 0, state->width, state->height);
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    perspectiveProjection(M_PI / 2.0f, state->width / (float) state->height, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);

    vec3 camPos = { 0, 0, 5 };
    camera(camPos);

    vec3 v0 = {  0.5,  -2.5,  0 };
    vec3 v1 = { -2.25,  0.25, 0 };
    vec3 v2 = {  0.25,  0.25, 0 };
    vec3 c  = { 0, 1, 0 };

    vec3 c2 = { 0, 0, 1 };
    drawTriangle(v0, v1, v2, c2);

    vec3 pos = { 0, 0, 0 };

    drawCircle(pos, 3, c, 30);

    return;
}

void freeGameState(GameState *state) {
    SDL_GL_DeleteContext(state->glContext);
    SDL_DestroyWindow(state->window);
}

void gameStateInit(GameState *state) {
    state->initialised = 1;
    state->state      = malloc(sizeof(PlayState));
    state->controller = malloc(sizeof(Controller));
    state->quit = 0;

    state->width = 1920 / 2;
    state->height = 1080 / 2;
}
