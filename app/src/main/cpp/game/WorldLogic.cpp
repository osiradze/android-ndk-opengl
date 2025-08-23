//
// Created by OSiradze on 29.07.25.
//


#include "GameRenderer.h"
#include "light/Light.h"
#include "objects/primitives/Cube.h"
#include "utils/MathUtils.h"
#include "../object_loader/ObjectLoader.h"
#include "objects/base/ShadersPaths.h"
#include "objects/texture/Texture.h"
#include "objects/GLObject.h"
#include <glm/glm.hpp>
#include <android/log.h>

void GameRenderer::initObject(){
    ShadersPaths objectShader {"shaders/object_v.vert", "shaders/object_f.frag" };
    ShadersPaths lightShaders { "shaders/object_v.vert", "shaders/light_f.frag" };

    Texture cubeTexture {"textures/cube_diffuse.png", "textures/cube_specular.png"};
    Texture floorTexture {"textures/floor_diffuse.png", "textures/floor_specular.png"};

    lantern = ObjectLoader::loadObject("models/lantern.obj");
    lantern->getTranslation()-> setScale(glm::vec3(5.f));
    lantern->getTranslation()-> setPosition(glm::vec3(0.0f, -0.1f, 0.0f));
    Texture lanternTexture{"textures/lantern_diffuse.png", "textures/lantern_specular.png"};
    gameObjects.push_back(std::make_unique<GLObject>(&env, lantern.get(), objectShader, lanternTexture));

    cube1->getTranslation()->setPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
    cube1->getTranslation()->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    gameObjects.push_back(std::make_unique<GLObject>(&env, cube1.get(), objectShader, cubeTexture));

    cube2->getTranslation()->setPosition(glm::vec3(1.0f, 0.0f, 0.0f));
    cube2->getTranslation()->setRotation(glm::vec3(0.0f, 45.0f, 0.0f));
    gameObjects.push_back(std::make_unique<GLObject>(&env, cube2.get(), objectShader, cubeTexture));


    lightCube1->getTranslation()->setPosition(env.lights[0].light_position);
    lightCube1->getTranslation()->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
    gameObjects.push_back(std::make_unique<GLObject>(&env, lightCube1.get(), lightShaders, std::nullopt));

    lightCube2->getTranslation()->setPosition(env.lights[1].light_position);
    lightCube2->getTranslation()->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
    gameObjects.push_back(std::make_unique<GLObject>(&env, lightCube2.get(), lightShaders, std::nullopt));

    floor->getTranslation()->setPosition(glm::vec3(0.0f, -0.5f, 1.0f));
    floor->getTranslation()->setScale(glm::vec3(7.0));
    gameObjects.push_back(std::make_unique<GLObject>(&env, floor.get(), objectShader, floorTexture));
}

void GameRenderer::updateObjects() {
    for(auto &light : env.lights) {
        light.rotate(60, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    lightCube1->getTranslation()->setPosition(env.lights[0].light_position);
    lightCube2->getTranslation()->setPosition(env.lights[1].light_position);
//    env.lights.light_color = MathUtils::rotate(env.lights.light_color, 1.0, glm::vec3(0.0f, 1.0f, 0.0f));
}