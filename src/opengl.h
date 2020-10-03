#ifndef gl_H
#define gl_H

#include <GL/gl.h>

typedef struct {
    float points[16];
} mat4;

typedef struct {
    float points[3];
} vec3;

void orthoProjection(float aspectRatio, float near, float far);
void perspectiveProjection(float aspectRatio, float fov, float near, float far);
void camera(vec3 position);

void drawTriangle(vec3 v0, vec3 v1, vec3 v2, vec3 c);
void drawRect(vec3 v0, vec3 v1, vec3 v2, vec3 v3, vec3 c);
void drawCircle(vec3 pos, float radius, vec3 c, int subDivs);

#endif
