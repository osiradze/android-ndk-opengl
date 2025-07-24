//
// Created by OSiradze on 23.07.25.
//

#pragma once

#include <glm/mat4x4.hpp> // mat4
using namespace glm;

class Camera {

public:

    mat4 view = mat4(1.0f);
    mat4 projection = mat4(1.0f);

    Camera(vec3 eye, vec3 center, vec3 up, float fov, float ratio, float nearPlane, float farPlane);
    void setRatio(float ratio);
    void setUniform(unsigned int view, unsigned int projection);

    static Camera createDefaultCamera() {
        return {
            vec3(3.0f, 3.0f, 3.0f),
            vec3(0.0f, 0.0f, 0.0f),
            vec3(0.0f, 1.0f, 0.0f),
            45.0f,
            1.0f,
            0.1f,
            100.0f
        };
    }

private:
    vec3 eye, center, up;
    float fov, ratio, nearPlane, farPlane;
};
