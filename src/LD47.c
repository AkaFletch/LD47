#include "LD47.h"
#include "PlayState.h"

void handleKeyboard(Controller *controller, SDL_Event event) {
    int keypressed = event.key.type == SDL_KEYDOWN;
    switch(event.key.keysym.sym) {
        case SDLK_SPACE: {
            controller->Accept.pressed = keypressed;
            break;
        }
        case SDLK_a: {
            controller->Left.pressed = keypressed;
            break;
        }
        case SDLK_d: {
            controller->Right.pressed = keypressed;
            break;
        }
        case SDLK_r: {
            controller->Reset.pressed = keypressed;
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
            case SDL_KEYUP: {
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

void updateGame(GameState *state, float delta) {
    handleInput(state, state->controller);
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( state->music, -1 );
        Mix_VolumeMusic(MIX_MAX_VOLUME/3);
    }
    if(state->controller->Exit.pressed) {
        state->quit = 1;
    }
    switch(state->state->type) {
        case LevelType_Play: {
            UpdatePlayState(&state->state->play, state->controller, delta);
            break;
        }
        case LevelType_None: {
            printf("Level type set to none?");
            state->quit = 1;
            return;
        }
    }
    return;
}

void render(GameState *state) {
    glViewport(0, 0, state->width, state->height);
    glClearColor(100.0/255, 149.0/255, 237.0/255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    perspectiveProjection(M_PI / 2.0f, state->width / (float) state->height, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);

    switch(state->state->type) {
        case LevelType_Play: {
            RenderPlayState(&state->state->play);
            break;
        }
        case LevelType_None: {
            printf("Level type set to none?");
            state->quit = 1;
            return;
        }
    }

    return;
}

void freeGameState(GameState *state) {
    free(state->controller);
    free(state->state);
    Mix_FreeMusic(state->music);
    SDL_GL_DeleteContext(state->glContext);
    SDL_DestroyWindow(state->window);
}

void gameStateInit(GameState *state) {
    state->initialised = 1;
    state->state = malloc(sizeof(LevelState));
    memset(state->state, 0, sizeof(LevelState));
    state->state->type = LevelType_Play;
    state->state->play.initialised = 0;
    state->controller = malloc(sizeof(Controller));
    memset(state->controller, 0, sizeof(Controller));
    state->quit = 0;
    state->music = Mix_LoadMUS("data/fastpiano.wav");

    state->width = 1920 / 2;
    state->height = 1080 / 2;
}
