//
// Created by OSiradze on 13.07.25.
//
#include "GameRenderer.h"
#include "light/Light.h"
#include "utils/MathUtils.h"
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
}

void GameRenderer::onDrawFrame() {
    updateObjects();

    screen->bind();
    drawObjects();
    screen->draw();

    handleColorIdPicking();
}

void GameRenderer::handleColorIdPicking() {
    if(touchDownEvent == nullptr) {
        return;
    }
    colorIdScreen->bind();
    env.colorIdMode = true;
    drawObjects();
    env.colorIdMode = false;

    auto colorId = colorIdScreen->getPixel(touchDownEvent->x, touchDownEvent->y);
    //colorIdScreen->draw();
    //__android_log_print(ANDROID_LOG_ERROR, "ColorId", "R: %f, G: %f, B: %f A: %f", colorId[0], colorId[1], colorId[2], colorId[3]);
    std::unique_ptr<GameObject> pickedObject;
    float epsilon = 0.02;
    for (auto &obj : allData) {
        auto match = MathUtils::areEqual(obj->colorId[0], colorId[0], epsilon)
                && MathUtils::areEqual(obj->colorId[1],colorId[1], epsilon)
                && MathUtils::areEqual(obj->colorId[2], colorId[2], epsilon);
        if(match) {
            obj->outline = !obj->outline;
            __android_log_print(ANDROID_LOG_ERROR, "ColorId", "Picked object: %s", obj->name.c_str());
        }
    }
    touchDownEvent.reset();
    touchDownEvent = nullptr;
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
    screen->destroy();
}

void GameRenderer::onDrag(float x, float y) {
    env.camera.rotate(-0.1f * x, glm::vec3(0.0f, 1.0f, 0.0f));
    env.camera.zoom(0.01f * y);
}

void GameRenderer::onTouchDown(int x, int y) {
    touchDownEvent = std::make_unique<TouchDown>( TouchDown { x, y });
}
