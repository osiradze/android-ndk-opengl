//
// Created by OSiradze on 06.08.25.
//

#include <GLES3/gl3.h>
#include "GameRenderer.h"

void GameRenderer::initGLConfig() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); // Accept fragments that are closer to the camera
    glEnable(GL_STENCIL_TEST);
}

void GameRenderer::clearBuffers() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
