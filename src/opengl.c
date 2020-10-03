#include "opengl.h"
#include "math.h"

void orthoProjection(float aspectRatio, float near, float far) {
    float a  = 1;
    float b = -aspectRatio;
    float c = 2.0 / (near - far);
    float d = (near + far) / (near - far);

    mat4 result = {
        a, 0, 0, 0,
        0, b, 0, 0,
        0, 0, c, d,
        0, 0, 0, 1
    };

    glMatrixMode(GL_PROJECTION);
    glLoadTransposeMatrixf((float *) &result);
}

void perspectiveProjection(float fov, float aspectRatio, float near, float far) {
    float focalLength = (1.0 / tan(0.5f * fov));

    float a = (focalLength / aspectRatio);
    float b = focalLength;
    float c = -(far - near) / (far - near);
    float d = -(2.0 * far * near) / (far - near);

    mat4 result = {
        a, 0, 0, 0,
        0, b, 0, 0,
        0, 0, c, d,
        0, 0, -1, 0
    };

    glMatrixMode(GL_PROJECTION);
    glLoadTransposeMatrixf((float *) &result);
}

void camera(vec3 position) {
    mat4 result = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };

    position.points[0] = -position.points[0];
    position.points[1] = -position.points[1];
    position.points[2] = -position.points[2];

    vec3 txp = position;

    result.points[3] += txp.points[0];
    result.points[7] += txp.points[1];
    result.points[11] += txp.points[2];

    glMatrixMode(GL_MODELVIEW);
    glLoadTransposeMatrixf((float *) &result);
}

void drawTriangle(vec3 v0, vec3 v1, vec3 v2, vec3 c) {
    glBegin(GL_TRIANGLES);
    glColor3f(c.points[0], c.points[1], c.points[2]);

    glVertex3fv(v0.points);
    glVertex3fv(v1.points);
    glVertex3fv(v2.points);

    glEnd();
}

void drawRect(vec3 v0, vec3 v1, vec3 v2, vec3 v3, vec3 c) {
    glBegin(GL_TRIANGLES);
    glColor3f(c.points[0], c.points[1], c.points[2]);

    glVertex3fv(v0.points);
    glVertex3fv(v1.points);
    glVertex3fv(v3.points);

    glVertex3fv(v1.points);
    glVertex3fv(v2.points);
    glVertex3fv(v3.points);

    glEnd();
}

void drawCircle(vec3 pos, float radius, vec3 c, int subDivs) {
    glBegin(GL_TRIANGLES);
    glColor3f(c.points[0], c.points[1], c.points[2]);

    float anglePerTurn = (2.0f * M_PI) / (float) subDivs;

    float angle = 0;
    for (int i = 0; i < subDivs; i++) {
        float x0 = pos.points[0] + (radius * cosf(angle));
        float y0 = pos.points[1] + (radius * sinf(angle));

        float x1 = pos.points[0] + (radius * cosf(angle + anglePerTurn));
        float y1 = pos.points[1] + (radius * sinf(angle + anglePerTurn));

        glVertex3f(pos.points[0], pos.points[1], pos.points[2]);
        glVertex3f(x0, y0, pos.points[3]);
        glVertex3f(x1, y1, pos.points[3]);

        angle += anglePerTurn;
    }

    glEnd();
}

