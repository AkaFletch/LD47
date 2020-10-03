#include "opengl.h"
#include "math.h"

mat4 OrthProjection(float aspectRatio, float near, float far) {
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

    return result;
}

mat4 Camera(vec3 position) {
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
    return result;
}

mat4 PerspectiveProjection(float fov, float aspectRatio, float near, float far) {
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
    return result; 
}
