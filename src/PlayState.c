#include "LD47.h"
#include <math.h>
#include <time.h>

float getDistance(vec3 p1, vec3 p2) {
    float x = p1.points[0] - p2.points[0];
    float y = p1.points[1] - p2.points[1];
    return sqrt(x*x + y*y);
}

vec3 closestPoint(vec3 p1, vec3 p2, vec3 r) {
    float A1 = p2.points[1] - p1.points[1];
    float B1 = p1.points[0] - p2.points[0];
    float C1 = A1*p1.points[0] + (B1)*p1.points[1];
    float C2 = -B1*r.points[0] + A1*r.points[1];
    float det = A1*A1 + B1*B1;
    float cx = 0; 
    float cy = 0; 
    if(det != 0){ 
        cx = ((A1*C1 - B1*C2)/det); 
        cy = ((A1*C2 + B1*C1)/det); 
    }else{
        cx = r.points[0]; 
        cy = r.points[1]; 
    } 
    vec3 val = {cx, cy, 0};
    return val;
}


int playerCometHit(vec3 playerRect[4], Comet c) {
    vec3 position = {0, c.height, 0};
    vec3 rotated = rotateVec3xy(position, c.angle);
    vec3 tmp = {1,1,1};
    float testX = rotated.points[0];
    float testY = rotated.points[1];
    int i;
    for(i = 0; i < 4; i++) {
        vec3 point1 = playerRect[i];
        int j = i+1;
        if(j == 4) {
            j = 0;
        }
        vec3 point2 = playerRect[j];
        vec3 check = closestPoint(point1, point2, rotated);
        float checkVal = fabs(getDistance(check, point1) + getDistance(check, point2) - getDistance(point1, point2));
        if(checkVal > 0.001) {
            continue;
        }
        if (0.3 > getDistance(check, rotated)) {
            return 1;
        }
    }
    return 0;
}

void RenderPlayState(PlayState *state) {
    vec3 circleCol1  = {0, 1, 0};
    vec3 c  = {0, 0.8, 0};
    vec3 c2 = {0, 0, 0.7};
    vec3 c3 = {1, 1, 0};
    vec3 sun = {30, 30, -50};
    drawCircle(sun, 30, c3, 100);
    int i;
    int j;
    drawRect(
        state->playerSquare[0],
        state->playerSquare[1],
        state->playerSquare[2],
        state->playerSquare[3],
        c2
    );

    vec3 pos = {0, 0, 0};
    for(i = 0; i < state->cometCount; i++) {
        Comet *c = &state->comets[i];
        vec3 red = {1, 0, 0};
        vec3 black = {0, 0, 0};
        if(!c->finished) {
            vec3 position = {0, c->height, 0};
            vec3 rotated = rotateVec3xy(position, c->angle);
            drawCircle(rotated, c->radius+0.1, black, 20);
        }
        int j;
        Particle p;
        for(j = 0; j < c->particleCount; j++) {
            p = c->particles[j];
            if(!p.alive) continue;
            vec3 position = {0, p.height, 0};
            vec3 rotated = rotateVec3xy(position, p.angle);
            drawCircle(rotated, p.radius+0.1, black, 20);
        }
        for(j = 0; j < c->particleCount; j++) {
            p = c->particles[j];
            if(!p.alive) continue;
            vec3 position = {0, p.height, 0};
            vec3 rotated = rotateVec3xy(position, p.angle);
            drawCircle(rotated, p.radius, red, 20);
        }
    }
    for(i = 0; i < state->cometCount; i++) {
        Comet *c = &state->comets[i];
        vec3 red = {1, 0, 0};
        if(!c->finished) {
            vec3 position = {0, c->height, 0};
            vec3 rotated = rotateVec3xy(position, c->angle);
            drawCircle(rotated, c->radius, red, 20);
        }
    }
    drawCircle(pos, 30, c, 160);
    drawCircle(state->cameraPos, 0.5, c, 3);
}

void addNewComets(PlayState *state, int num) {
    int i;
    for(i = 0; i < num && state->cometCount<250; i++) {
        Comet *c = &state->comets[state->cometCount];
        c->finished = 0;
        c->spawnAngle = -((float)rand())/((float)RAND_MAX) * 2*M_PI;
        c->Spawnheight = rand() % 7 + 38;
        c->height = c->Spawnheight;
        c->radius = 0.3;
        c->rotation = 0.0011-((float)rand())/((float)RAND_MAX) * 0.003f;
        c->angle = c->spawnAngle;
        c->speed = 0.045 + 0.0015 - ((float)rand())/((float)RAND_MAX) * 0.003f;
        c->particleCount = 0;
        state->cometCount += 1;
    }
}

void addNewComet(PlayState *state) {
    if(state->rotationAngle < -2 * M_PI) {
        state->rotationAngle += 2*M_PI;
        state->player.angle += 2*M_PI;
        addNewComets(state, 24);
    }
    int i;
    for(i = 0; i < state->cometCount; i++) {
        Comet *c  = &state->comets[i];
        float spawnToUse = c->spawnAngle;
        int check = spawnToUse > state->rotationAngle + M_PI;
        if(spawnToUse < -M_PI && state->rotationAngle > -M_PI) {
            check = spawnToUse + M_PI > state->rotationAngle;
        }
        if(check) {
            c->finished = 0;
            c->height = c->Spawnheight;
            c->angle = c->spawnAngle;
            c->particleCount = 0;
            memset(c->particles,0,230*sizeof(Particle));
        }
    }
}

void resetPlayState(PlayState *state) {
    memset(state, 0, sizeof(LevelState));
}

void UpdatePlayState(PlayState *state, Controller *controller, float delta) {
    if(!state->initialised) {
        time_t t;
        srand((unsigned) time(&t));
        state->cameraPos.points[0] = 0;
        state->cameraPos.points[1] = 33;
        state->cameraPos.points[2] = 5;
        state->rotationAngle = 0;
        camera(state->cameraPos);
        
        state->player.height = 29.9;
        state->player.onFloor = 1;
        state->initialised = 1;
        state->player.angle = 0;
        state->time = 0;
        vec3 v1 = {0.25, state->player.height, 0};
        vec3 v2 = {-0.25, state->player.height, 0};
        vec3 v3 = {-0.25, state->player.height + 1, 0};
        vec3 v4 = {0.25, state->player.height + 1, 0};
        state->playerSquare[0] = rotateVec3xy(v1, state->player.angle);
        state->playerSquare[1] = rotateVec3xy(v2, state->player.angle);
        state->playerSquare[2] = rotateVec3xy(v3, state->player.angle);
        state->playerSquare[3] = rotateVec3xy(v4, state->player.angle);
        addNewComets(state, 23);
    }
    if(!state->started) {
        if(controller->Accept.pressed) {
            state->started = 1;
            controller->Accept.pressed=0;
        }
        return;
    }
    state->time+=delta;
    vec3 newCamPos = {0.0, 33.0, 5};
    state->cameraPos = rotateVec3xy(newCamPos, state->rotationAngle);
    float rotationProgress = fabs(cosf(state->rotationAngle));
    float bound = 0.3 * rotationProgress + 0.3;
    if(controller->Left.pressed && state->rotationAngle - state->player.angle > -bound/2) {
        state->player.angle += 0.0025;
    }
    else if(controller->Right.pressed && state->player.angle - state->rotationAngle > -bound/2) {
        state->player.angle -= 0.0025;
    }
    if(state->player.angle > state->rotationAngle + bound/2) {
        state->player.angle = state->rotationAngle + bound/2;
    } 
    else if(state->player.angle < state->rotationAngle - bound/2) {
        state->player.angle = state->rotationAngle - bound/2;
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
        int rotateCatch = state->rotationAngle - 2*M_PI + 0.3f > comet->spawnAngle;
        float angle = comet->spawnAngle;
        int j;
        for(j = 0; j < comet->particleCount; j++) {
            Particle *p = &comet->particles[j];
            if(!p->alive) continue;
            p->radius -= 0.001*delta;
            if(p->radius < 0) {
                p->alive = 0;
                p->radius = ((float)rand())/((float)RAND_MAX) * 0.16;
            }
        }
        if(comet->finished) {
            continue;
        }
        else if(comet->height < comet->radius + 30) {
            comet->finished = 1;
        }
        if(comet->spawnAngle + 0.3f > state->rotationAngle || rotateCatch) {
            comet->height -= comet->speed*delta;
            comet->angle = comet->angle + comet->rotation*delta;
            comet->particleTime += delta;
            if(comet->particleTime > 0.005) {
                if(comet->particleCount != 230) {
                    comet->particleTime = 0;
                    Particle *p = &(comet->particles[comet->particleCount]);
                    p->alive = 1;
                    p->angle = comet->angle + 0.01-((float)rand())/((float)RAND_MAX) * 0.02;
                    p->height = comet->height;
                    p->radius = ((float)rand())/((float)RAND_MAX) * 0.20;
                    comet->particleCount += 1;
                }
            }
        }
    }
    for(i = 0; i < state->cometCount; i++) {
        if(!state->comets[i].finished && playerCometHit(state->playerSquare, state->comets[i])){
            state->gameover = 1;
            resetPlayState(state);
            state->cameraPos.points[0] = 0;
            state->cameraPos.points[1] = 33;
            state->cameraPos.points[2] = 5;
            state->rotationAngle = 0;
            camera(state->cameraPos);
            break;
        }
    }

    addNewComet(state);
    camera(state->cameraPos);
    state->rotationAngle -= 0.002f * delta;
    state->player.angle -= 0.002f * delta;
    if(controller->Reset.pressed && state->time>200) {
        resetPlayState(state);
    }
}
