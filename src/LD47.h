#ifndef LD47_H
#define LD47_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include "opengl.h"

typedef enum LevelType {
    LevelType_None = 0,
    LevelType_Play,
} LevelType;

typedef struct Particle {
    int alive;
    float radius;
    float height;
    float angle;
} Particle;

typedef struct Comet {
    int finished;
    int frame;
    int seed;
    float height;
    float Spawnheight;
    float radius;
    float rotation;
    float spawnAngle;
    float angle;
    float speed;
    float particleTime;
    int particleCount;
    Particle particles[230];
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
    int started;
    int gameover;
    vec3 cameraPos;
    vec3 playerSquare[4];
    float rotationAngle;
    Player player;
    Box boxes[20];
    int boxCount;
    Comet comets[260];
    int cometCount;
    int spawnedNewComet;
    float time;
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
    GameButton Reset;
} Controller;

typedef struct GameState {
    int initialised;

    int width, height;
    SDL_Window *window;

    SDL_GLContext *glContext;
    Controller *controller;
    LevelState *state;
    Mix_Music *music;
    int quit;
} GameState;

void updateGame(GameState *state, float delta);
void render(GameState *state);
void freeGameState(GameState *state);
void gameStateInit(GameState *state);

#endif
