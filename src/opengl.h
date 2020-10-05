#ifndef gl_H
#define gl_H

#include <GL/gl.h>

typedef struct {
    float points[16];
} mat4;

typedef struct {
    float points[4];
} mat2;

typedef struct {
    float points[3];
} vec3;

typedef struct {
    float points[2];
} vec2;

void orthoProjection(float aspectRatio, float near, float far);
void perspectiveProjection(float aspectRatio, float fov, float near, float far);
void camera(vec3 position);

void drawTriangle(vec3 v0, vec3 v1, vec3 v2, vec3 c);
void drawRect(vec3 v0, vec3 v1, vec3 v2, vec3 v3, vec3 c);
void drawLine(vec3 first, vec3 second);
void drawCircle(vec3 pos, float radius, vec3 c, int subDivs);
vec3 rotateVec3xy(vec3 rotate, float angle);

#endif
