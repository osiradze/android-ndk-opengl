//
// Created by OSiradze on 03.08.25.
//

#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct Translation {

private:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::mat4 model = glm::mat4(1.0f);
public:
    void move(const glm::vec3 p) {
        this->position += p;
        updateModelMatrix();
    }
    void setPosition(const glm::vec3 p) {
        this->position = p;
        updateModelMatrix();
    }

    void setScale(const glm::vec3 s) {
        this->scale = s;
        updateModelMatrix();
    }

    void setRotation(const glm::vec3 r) {
        this->rotation = r;
        updateModelMatrix();
    }

    void rotate(const glm::vec3 r) {
        this->rotation += r;
        updateModelMatrix();
    }

    glm::mat4 getModel() {
        return model;
    }

private:
    void updateModelMatrix() {
        // Convert Euler angles to quaternion
        glm::quat q = glm::quat( glm::radians(rotation));

        // Convert quaternion to rotation matrix
        glm::mat4 rot = glm::toMat4(q);

        // Combine: T * R * S (order matters!)
        model = glm::translate(glm::mat4(1.0f), position);
        model *= rot;
        model = glm::scale(model, scale);
    }
};