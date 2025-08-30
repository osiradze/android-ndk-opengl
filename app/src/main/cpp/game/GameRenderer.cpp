//
// Created by OSiradze on 13.07.25.
//
#include "light/Light.h"
#include "GameRenderer.h"
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
    line->init();
    particles->init();
}

void GameRenderer::onDrawFrame() {
    updateObjects();
    copyTouchTmp();
    screen->bind();
    drawObjects();
    screen->draw();

    handleColorIdPicking();
    touch->reset();
}

void GameRenderer::drawObjects() {
    clearBuffers();
    for (auto &obj : gameObjects) {
        if (obj) {
            obj->onDraw();
        }
    }
    line->onDraw();
    particles->onDraw();
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
    particles->destroy();

    for(auto &data : allData) {
        if (data) {
            data->freeVertexDataFromMemory();
        }
    }
}
