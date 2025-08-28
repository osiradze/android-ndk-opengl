//
// Created by OSiradze on 28.08.25.
//

#include <android/log.h>
#include "GameRenderer.h"
#include "utils/MathUtils.h"

void GameRenderer::handleColorIdPicking() {
    if(touchDownEvent == nullptr) {
        return;
    }
    colorIdScreen->bind();
    env.colorIdMode = true;
    drawObjects();
    env.colorIdMode = false;

    auto colorId = colorIdScreen->getPixel(touchDownEvent->x, touchDownEvent->y);
    float epsilon = 0.01;
    for (auto &obj : allData) {
        auto match = MathUtils::match(obj->colorId, colorId, 3, epsilon);
        if(match) {
            //obj->outline = !obj->outline;
            break;
        }
    }
}

void GameRenderer::onDrag(float x, float y) {
    //env.camera.rotate(-0.1f * x, glm::vec3(0.0f, 1.0f, 0.0f));
    //env.camera.zoom(0.01f * y);
}

void GameRenderer::onTouchDown(int x, int y) {
    touchDownEvent->start = true;
    setTouchCoordinates(x, y);
}

void GameRenderer::onTouch(int x, int y) {
    if(!touchDownEvent->active) {
        touchDownEvent->start = true;
    }
    touchDownEvent->active = true;
    setTouchCoordinates(x, y);
}

void GameRenderer::onTouchUp(int x, int y) {
    touchDownEvent->active = false;
    setTouchCoordinates(x, y);
}


void GameRenderer::setTouchCoordinates(int x, int y) {
    touchDownEvent->x = x;
    touchDownEvent->y = y;
    touchDownEvent->floatX = (2.0f * x) / screen->width - 1.0f;
    touchDownEvent->floatY = 1.0f - (2.0f * y) / screen->height;
}

