//
// Created by OSiradze on 13.07.25.
//
#include "GameRenderer.h"
#include "light/Light.h"
#include <glm/glm.hpp>

void GameRenderer::onSurfaceCreated() {
    initGLConfig();
    initObject();
    for (auto &obj : gameObjects) {
        if (obj) {
            obj->init();
        }
    }
}

void GameRenderer::onDrawFrame() {
    clearBuffers();
    updateObjects();
    for (auto &obj : gameObjects) {
        if (obj) {
            obj->onDraw();
        }
    }
}

void GameRenderer::onSurfaceChanged(int width, int height) {
    env.camera.setRatio(static_cast<float>(width) / static_cast<float>(height));
}

void GameRenderer::onDestroy() {
    for (auto &obj : gameObjects) {
        if (obj) {
            obj->destroy();
        }
    }
}

void GameRenderer::onDrag(float x, float y) {
    env.camera.rotate(-0.1f * x, glm::vec3(0.0f, 1.0f, 0.0f));
    env.camera.rotate(-0.1f * y, glm::vec3(1.0f, 0.0f, 0.0f));
}
