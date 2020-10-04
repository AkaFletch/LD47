#include "LD47.h"
#include <math.h>

void RenderPlayState(PlayState *state) {
    vec3 circleCol1  = {0, 1, 0};
    vec3 c  = {0, 1, 0};
    vec3 c2 = {0, 0, 1};

    drawRect(
        state->playerSquare[0],
        state->playerSquare[1],
        state->playerSquare[2],
        state->playerSquare[3],
        c2
    );

    vec3 pos = {0, 0, 0};
    vec3 c3 = {1, 1, 0};
    int i;
    for(i = 0; i < state->boxCount; i++) {
        Box b = state->boxes[i];
        vec3 v1 = {b.pos.points[0] + b.size.points[0],  b.pos.points[1],  0};
        vec3 v2 = {b.pos.points[0] + b.size.points[0],  b.pos.points[1] + b.size.points[1],  0};
        vec3 v3 = {b.pos.points[0] - b.size.points[0],  b.pos.points[1] + b.size.points[1],  0};
        vec3 v4 = {b.pos.points[0] - b.size.points[0],  b.pos.points[1],  0};
        drawRect(v1, v2, v3, v4, c3);
    }
    for(i = 0; i < state->cometCount; i++) {
        if(state->comets[i].finished) {
            continue;
        }
        vec3 red = {1, 0, 0};
        drawCircle(state->comets[i].pos, state->comets[i].radius, red, 20);
    }
    drawCircle(pos, 30, c, 160);
}

void addNewComet(PlayState *state) {
    if(state->rotationAngle < -2 * M_PI) {
        state->rotationAngle = 0;
        int i;
        for(i = 0; i < state->cometCount; i++) {
            if(state->comets[i].finished) {
                state->comets[i].finished = 0;
                state->comets[i].pos = state->comets[i].spawnPos;
            }
        }
        // TODO Add a new comet
    }
    else if(state->rotationAngle < -M_PI) {
        int i;
        for(i = 0; i < state->cometCount; i++) {
            if(state->comets[i].finished) {
                state->comets[i].finished = 0;
                state->comets[i].pos = state->comets[i].spawnPos;
            }
        }
    }
}

void UpdatePlayState(PlayState *state, Controller *controller, float delta) {
    if(!state->initialised) {
        state->cameraPos.points[0] = 0;
        state->cameraPos.points[1] = 30;
        state->cameraPos.points[2] = 5;
        state->rotationAngle = 0;

        state->player.height = 29.9;
        state->player.onFloor = 1;
        state->initialised = 1;
        state->boxes[0].alive = 1;
        state->boxes[0].pos.points[0] = 0;
        state->boxes[0].pos.points[1] = 29.9;
        state->boxes[0].pos.points[2] = 20;
        state->boxes[0].size.points[0] = 0.5;
        state->boxes[0].size.points[1] = 1;
        state->boxCount = 1;

        state->cometCount = 1;
        state->comets[0].finished = 0;
        state->comets[0].spawnAngle = -0.1;
        state->comets[0].pos.points[0] = 0;
        state->comets[0].pos.points[1] = 35;
        state->comets[0].pos.points[2] = 0;
        state->comets[0].spawnPos = state->comets[0].pos;
        state->comets[0].radius = 0.3;
    }
    vec3 newCamPos = {0.0, 33.0, 5};
    state->cameraPos = rotateVec3xy(newCamPos, state->rotationAngle);

    if(controller->Left.pressed) {
        state->player.angle += 0.003;
    }
    else if(controller->Right.pressed) {
        state->player.angle -= 0.003;
    }
    if(controller->Accept.pressed && state->player.onFloor) {
        state->player.onFloor = 0;
        state->player.yVelocity = 0.05*delta;
    }
    else if(!state->player.onFloor) {
        state->player.yVelocity -= 0.003;
        state->player.height += state->player.yVelocity*delta;
        if(state->player.height < 29.9) {
            state->player.height = 29.9;
            state->player.onFloor = 1;
            state->player.yVelocity = 0;
        }
    }

    vec3 v1 = {0.25, state->player.height, 0};
    vec3 v2 = {-0.25, state->player.height, 0};
    vec3 v3 = {-0.25, state->player.height + 1, 0};
    vec3 v4 = {0.25, state->player.height + 1, 0};
    state->playerSquare[0] = rotateVec3xy(v1, state->player.angle);
    state->playerSquare[1] = rotateVec3xy(v2, state->player.angle);
    state->playerSquare[2] = rotateVec3xy(v3, state->player.angle);
    state->playerSquare[3] = rotateVec3xy(v4, state->player.angle);
    int i;
    for(i = 0; i < state->cometCount; i++) {
        Comet *comet = &state->comets[i];
        if(comet->finished) {
            continue;
        }
        if(comet->pos.points[1] < comet->radius + 30) {
            comet->finished = 1;
        }
        if(comet->spawnAngle < state->rotationAngle) {
            comet->pos.points[1] -= 0.045*delta;
        }
    }

    camera(state->cameraPos);
    state->rotationAngle -= 0.001f * delta;
    addNewComet(state);
}
