//
// Created by OSiradze on 13.07.25.
//
#include "GameRenderer.h"
#include "objects/box/Box.cpp"
#include <glm/glm.hpp>

void GameRenderer::onSurfaceCreated() {
    Camera* cameraPtr = &camera;
    gameObjects[0] = new Box(cameraPtr, glm::mat4(1.0f));
    for (GameObject* obj : gameObjects) {
        if (obj) {
            obj->init();
        }
    }
}

void GameRenderer::onDrawFrame() {
    camera.rotate(0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
    for (GameObject* obj : gameObjects) {
        if (obj) {
            obj->onDraw();
        }
    }
}

void GameRenderer::onSurfaceChanged(int width, int height) {
    camera.setRatio(static_cast<float>(width) / static_cast<float>(height));
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
