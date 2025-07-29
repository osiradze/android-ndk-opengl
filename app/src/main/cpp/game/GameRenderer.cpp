//
// Created by OSiradze on 13.07.25.
//
#include "GameRenderer.h"
#include "objects/base/GLObjectImpl.cpp"
#include "light/Light.h"
#include "objects/box/Cube.h"
#include <glm/glm.hpp>

void GameRenderer::onSurfaceCreated() {
    gameObjects[0] = new GLObjectImpl(&env, &(cube.data));

    for (GameObject* obj : gameObjects) {
        if (obj) {
            obj->init();
        }
    }
}

void GameRenderer::onDrawFrame() {
    env.light.rotate(40, glm::vec3(0.0f, 1.0f, 0.0f));

    for (GameObject* obj : gameObjects) {
        if (obj) {
            obj->onDraw();
        }
    }
}

void GameRenderer::onSurfaceChanged(int width, int height) {
    env.camera.setRatio(static_cast<float>(width) / static_cast<float>(height));
    for (GameObject* obj : gameObjects) {
        if (obj) {
            obj->resize(width, height);
        }
    }
}

void GameRenderer::onDestroy() {
    for (GameObject* obj : gameObjects) {
        if (obj) {
            obj->destroy();
            delete obj;
        }
    }
}

void GameRenderer::onDrag(float x, float y) {
    env.camera.rotate(-0.1f * x, glm::vec3(0.0f, 1.0f, 0.0f));
    env.camera.rotate(-0.1f * y, glm::vec3(1.0f, 0.0f, 0.0f));
}
