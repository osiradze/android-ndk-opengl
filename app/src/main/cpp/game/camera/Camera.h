//
// Created by OSiradze on 23.07.25.
//

#pragma once

#include <glm/mat4x4.hpp> // mat4

class Camera {

public:

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, float fov, float ratio, float nearPlane, float farPlane);
    void setRatio(float ratio);
    void rotate(float angle, glm::vec3 vector);

    void setUniform(unsigned int view, unsigned int projection);

    static Camera createDefaultCamera() {
        return {
            glm::vec3(3.0f, 3.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            45.0f,
            1.0f,
            0.1f,
            100.0f
        };
    }

private:
    glm::vec3 eye, center, up;
    float fov, ratio, nearPlane, farPlane;
};
