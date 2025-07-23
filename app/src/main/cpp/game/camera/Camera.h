//
// Created by OSiradze on 23.07.25.
//

#pragma once

#include <glm/mat4x4.hpp> // glm::mat4

class Camera {

public:
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    Camera(glm::vec3 position, float fov, float ratio, float nearPlane, float farPlane);
    void setRatio(float ratio);

    static Camera createDefaultCamera() {
        return {glm::vec3(0.0f, 0.0f, -3.0f), 45.0f, 1.0f, 0.1f, 100.0f};
    }

private:
    float fov, ratio, nearPlane, farPlane;
};
