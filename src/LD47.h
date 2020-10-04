#ifndef LD47_H
#define LD47_H
#include "SDL2/SDL.h"

#include "opengl.h"

typedef enum LevelType {
    LevelType_None = 0,
    LevelType_Play,
} LevelType;

typedef struct Comet {
    int finished;
    int frame;
    int seed;
    vec3 spawnPos;
    vec3 pos;
    float radius;
    float rotation;
    float spawnAngle;
} Comet;

typedef struct Box {
    int alive;
    vec3 pos;
    vec2 size;
    vec3 colour;
} Box;

typedef struct Player {
    float angle;
    int onFloor;
    float height;
    float yVelocity;
} Player;

typedef struct PlayState {
    int initialised;
    vec3 cameraPos;
    vec3 playerSquare[4];
    float rotationAngle;
    Player player;
    Box boxes[20];
    int boxCount;
    Comet comets[150];
    int cometCount;
    int spawnedNewComet;
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
    GameButton Left;
    GameButton Right;
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

void updateGame(GameState *state, float delta);
void render(GameState *state);
void freeGameState(GameState *state);
void gameStateInit(GameState *state);

#endif
