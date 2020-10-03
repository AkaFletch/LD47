#ifndef gl_H
#define gl_H

typedef struct {
    float points[16];
} mat4;

typedef struct {
    float points[3];
} vec3;

mat4 OrthProjection(float aspectRatio, float near, float far);
mat4 PerspectiveProjection(float aspectRatio, float fov, float near, float far);
mat4 Camera(vec3 position);

#endif
