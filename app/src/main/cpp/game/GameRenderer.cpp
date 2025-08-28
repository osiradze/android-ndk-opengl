//
// Created by OSiradze on 13.07.25.
//
#include "GameRenderer.h"
#include "light/Light.h"
#include <glm/glm.hpp>
#include <android/log.h>

void GameRenderer::onSurfaceCreated() {
    initGLConfig();
    initObject();

    for (auto &obj : gameObjects) {
        if (obj) {
            obj->init();
        }
    }
    for(auto &data : allData) {
        if (data) {
            data->freeVertexDataFromMemory();
        }
    }
    line->init();
}

void GameRenderer::onDrawFrame() {
    updateObjects();

    screen->bind();
    drawObjects();
    line->onDraw();
    screen->draw();

    handleColorIdPicking();
    touchDownEvent->reset();
}

void GameRenderer::drawObjects() {
    clearBuffers();
    for (auto &obj : gameObjects) {
        if (obj) {
            obj->onDraw();
        }
    }
}


void GameRenderer::onSurfaceChanged(int width, int height) {
    screen = std::make_unique<Screen>(width, height);
    colorIdScreen = std::make_unique<Screen>(width, height);
    env.camera.setRatio(static_cast<float>(width) / static_cast<float>(height));
}

void GameRenderer::onDestroy() {
    for (auto &obj : gameObjects) {
        if (obj) {
            obj->destroy();
        }
    }
    line->destroy();
    screen->destroy();
}
