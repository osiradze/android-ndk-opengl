//
// Created by OSiradze on 09.08.25.
//

#pragma once

#include "base/GameObject.h"
#include "base/GameObjectData.h"
#include "../environment/Environment.h"
#include "base/ShadersPaths.h"
#include "texture/Texture.h"
#include "shaders/Program.h"


class GLObject : public GameObject {
public:
    GLObject(
            Environment *env,
            GLObjectData *data,
            ShadersPaths shaders,
            std::optional<Texture> texturePath,
            bool outline = false
    ):
    env(env),
    data(data),
    shaders(std::move(shaders)),
    texturePath(std::move(texturePath)),
    outline(outline) {}

    void init() override;
    void onDraw() override;
    void destroy() override;

private:
    Environment *env;
    GLObjectData *data;
    ShadersPaths shaders;

    Program shaderProgram;
    Program stencilProgram;
    Program colorIdProgram;

    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;

    std::optional<Texture> texturePath;
    static const unsigned int numberOfTextures = 2;
    unsigned int texture[numberOfTextures]{};
    int textureLocations[numberOfTextures]{};

    bool outline = false;

    void initData();
    void initTexture();
    void initUniforms();
    void activateTextures();
    void updateUniforms(Program &program);
    void setUpDrawStencil() const;
    void drawOutLine();
};