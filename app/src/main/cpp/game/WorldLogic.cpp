//
// Created by OSiradze on 29.07.25.
//


#include "GameRenderer.h"
#include "objects/GLObjectImpl.cpp"
#include "light/Light.h"
#include "objects/primitives/Cube.h"
#include "utils/MathUtils.h"
#include "../object_loader/ObjectLoader.h"
#include <glm/glm.hpp>
#include <android/log.h>

void GameRenderer::initObject(){

    ShadersPaths objectShader {"shaders/object_v.vert", "shaders/object_f.frag" };
    lantern = ObjectLoader::loadObject("models/lantern.obj");
    lantern->getTranslation()-> setScale(glm::vec3(5.f));
    lantern->getTranslation()-> setPosition(glm::vec3(0.0f, -0.1f, 0.0f));
    Texture lanternTexture{"textures/lantern_diffuse.png", "textures/lantern_specular.png"};
    gameObjects[0] = new GLObjectImpl(&env, lantern.get(), objectShader, lanternTexture);


    Texture cubeTexture {"textures/cube_diffuse.png", "textures/cube_specular.png"};

    cube1.data.getTranslation()->setPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
    cube1.data.getTranslation()->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    gameObjects[1] = new GLObjectImpl(&env, &(cube1.data), objectShader, cubeTexture);

    cube2.data.getTranslation()->setPosition(glm::vec3(1.0f, 0.0f, 0.0f));
    cube2.data.getTranslation()->setRotation(glm::vec3(0.0f, 45.0f, 0.0f));
    gameObjects[2] = new GLObjectImpl(&env, &(cube2.data), objectShader, cubeTexture, true);


    ShadersPaths lightShaders { "shaders/object_v.vert", "shaders/light_f.frag" };
    lightCube.data.getTranslation()->setPosition(env.light.light_position);
    lightCube.data.getTranslation()->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
    gameObjects[3] = new GLObjectImpl(&env, &(lightCube.data), lightShaders, std::nullopt);

    Texture floorTexture {"textures/floor_diffuse.png", "textures/floor_specular.png"};
    floor.data.getTranslation()->setPosition(glm::vec3(0.0f, -0.5f, 1.0f));
    floor.data.getTranslation()->setScale(glm::vec3(7.0));
    gameObjects[4] = new GLObjectImpl(&env, &(floor.data), objectShader, floorTexture);
}

void GameRenderer::updateObjects() {
    env.light.rotate(60, glm::vec3(0.0f, 1.0f, 0.0f));
    lightCube.data.getTranslation()->setPosition(env.light.light_position);
    env.light.light_color = MathUtils::rotate(env.light.light_color, 1.0, glm::vec3(0.0f, 1.0f, 0.0f));
}