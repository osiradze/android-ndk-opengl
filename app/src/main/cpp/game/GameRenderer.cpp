//
// Created by OSiradze on 13.07.25.
//
#include "GameRenderer.h"

const void GameRenderer::onSurfaceCreated() {
    triangle -> init();
}

const void GameRenderer::onDrawFrame() {
    triangle -> onDraw();
}

const void GameRenderer::onSurfaceChanged(int width, int height) {
    triangle -> resize(width, height);
}

const void GameRenderer::onDestroy() {
    triangle -> destroy();
}
