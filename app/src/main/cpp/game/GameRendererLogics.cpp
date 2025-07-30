//
// Created by OSiradze on 29.07.25.
//


#include "GameRenderer.h"
#include "objects/GLObjectImpl.cpp"
#include "light/Light.h"
#include "objects/box/Cube.h"
#include "utils/MathUtils.h"
#include <glm/glm.hpp>

void GameRenderer::initLogics(){
    ShadersPaths cubeShaders { "shaders/object_v.vert", "shaders/object_f.frag" };
    gameObjects[0] = new GLObjectImpl(&env, &(cube.data),cubeShaders);

    cube2.data.model = glm::translate(glm::mat4(1.0), glm::vec3(-1.0f, 0.0f, 1.0f));
    cube2.data.model = glm::rotate(cube2.data.model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    gameObjects[1] = new GLObjectImpl(&env, &(cube2.data),cubeShaders);

    cube3.data.model = glm::translate(glm::mat4(1.0), glm::vec3(1.0f, 0.0f, -1.0f));
    cube3.data.model = glm::rotate(cube3.data.model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    gameObjects[2] = new GLObjectImpl(&env, &(cube3.data),cubeShaders);


    ShadersPaths lightShaders { "shaders/object_v.vert", "shaders/light_f.frag" };
    lightScaleModel = glm::scale(lightScaleModel, glm::vec3(0.2f, 0.2f, 0.2f));
    lightCube.data.model = glm::translate(glm::mat4(1.0), env.light.light_position) * lightScaleModel;
    gameObjects[3] = new GLObjectImpl(&env, &(lightCube.data), lightShaders );

}

void GameRenderer::drawLogics() {
    env.light.rotate(60, glm::vec3(0.0f, 1.0f, 0.0f));
    lightCube.data.model = glm::translate(glm::mat4(1.0), env.light.light_position) * lightScaleModel;
    env.light.light_color = MathUtils::rotate(env.light.light_color, 1.0, glm::vec3(0.0f, 1.0f, 0.0f));

}