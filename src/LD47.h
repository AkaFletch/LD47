#ifndef LD47_H
#define LD47_H
#include "SDL2/SDL.h"

#include "opengl.h"

typedef enum LevelType {
    LevelType_None = 0,
    LevelType_Play,
} LevelType;

typedef struct PlayState {

} PlayState;

typedef struct LevelState {
    LevelType type;
    union {
        PlayState play;
    };
} LevelState;

typedef struct GameButton {
    unsigned long transitions;
    int pressed;
} GameButton;

typedef struct Controller {
    GameButton Exit;
    GameButton Accept;
} Controller;

typedef struct GameState {
    int initialised;

    int width, height;
    SDL_Window *window;

    SDL_GLContext *glContext;
    Controller *controller;
    LevelState *state;
    int quit;
} GameState;

void updateGame(GameState *state);
void render(GameState *state);
void freeGameState(GameState *state);
void gameStateInit(GameState *state);

#endif
