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
            obj->outline = !obj->outline;
            break;
        }
    }
    touchDownEvent.reset();
    touchDownEvent = nullptr;
}

void GameRenderer::onDrag(float x, float y) {
    env.camera.rotate(-0.1f * x, glm::vec3(0.0f, 1.0f, 0.0f));
    env.camera.zoom(0.01f * y);
}

void GameRenderer::onTouchDown(int x, int y) {
    touchDownEvent = std::make_unique<TouchDown>( TouchDown { x, y });
}

