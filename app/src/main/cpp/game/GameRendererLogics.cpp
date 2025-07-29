//
// Created by OSiradze on 29.07.25.
//


#include "GameRenderer.h"
#include "objects/base/GLObjectImpl.cpp"
#include "light/Light.h"
#include "objects/box/Cube.h"
#include <glm/glm.hpp>

void GameRenderer::initLogics(){
    gameObjects[0] = new GLObjectImpl(&env, &(cube.data),ShadersPaths { "shaders/object_v.vert", "shaders/object_f.frag"});
    lightScaleModel = glm::scale(lightScaleModel, glm::vec3(0.2f, 0.2f, 0.2f));
    lightCube.data.model = glm::translate(glm::mat4(1.0), env.light.light_position) * lightScaleModel;
    gameObjects[1] = new GLObjectImpl(&env, &(lightCube.data), ShadersPaths { "shaders/object_v.vert", "shaders/light_f.frag"});
}

void GameRenderer::drawLogics() {
    env.light.rotate(60, glm::vec3(0.0f, 1.0f, 0.0f));
    lightCube.data.model = glm::translate(glm::mat4(1.0), env.light.light_position) * lightScaleModel;
}