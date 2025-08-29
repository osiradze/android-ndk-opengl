//
// Created by OSiradze on 28.08.25.
//

#include <android/log.h>
#include "GameRenderer.h"
#include "utils/MathUtils.h"

void GameRenderer::handleColorIdPicking() {
    if(touch == nullptr) {
        return;
    }
    colorIdScreen->bind();
    env.colorIdMode = true;
    drawObjects();
    env.colorIdMode = false;

    auto colorId = colorIdScreen->getPixel(touch->x, touch->y);
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
    //touchDownEvent->start = true;
    //setTouchCoordinates(x, y);
}

void GameRenderer::onTouch(int x, int y) {
    if(touchTmp != nullptr) {
        return;
    }
    touchTmp = std::make_unique<TouchDownTmp>( TouchDownTmp {
        .x = x,
        .y = y,
        .floatX = (2.0f * x) / screen->width - 1.0f,
        .floatY = 1.0f - (2.0f * y) / screen->height
    });
}

void GameRenderer::onTouchUp(int x, int y) {
    touchTmp = std::make_unique<TouchDownTmp>( TouchDownTmp {
        .touchUp = true,
    });
    //setTouchCoordinates(x, y);
}


void GameRenderer::copyTouchTmp() {
    if(touchTmp == nullptr) {
        return;
    }
    if(touchTmp->touchUp) {
        touch->active = false;
        touchTmp.reset();
        return;
    }
    touch->x = touchTmp->x;
    touch->y = touchTmp->y;
    touch->floatX = touchTmp->floatX;
    touch->floatY = touchTmp->floatY;
    if(!touch->active) {
        touch->start = true;
    }
    touch->active = true;

    touchTmp.reset();
}

