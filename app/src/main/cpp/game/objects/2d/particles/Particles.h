//
// Created by OSiradze on 30.08.25.
//

#pragma once

#include "../../GameObject.h"
#include "../../shaders/Uniforms.h"
#include "../../shaders/ShadersPaths.h"
#include "ParticlesData.h"
#include "../../../environment/Environment.h"


class Particles: GameObject {
public:
    explicit Particles(
            Environment *env,
            GLObjectData* objectDataPtr
): env(env), data(std::make_unique<ParticlesData>(objectDataPtr)), objectDataPtr(objectDataPtr){}

    void init() override;
    void onDraw() override;
    void destroy() override;

private:
    Environment *env;
    std::unique_ptr<ParticlesData> data;
    GLObjectData* objectDataPtr;

    ShadersPaths shaders = {
            .vertexShader = "shaders/particles/particles_v.vert",
            .fragmentShader = "shaders/particles/particles_f.frag",
            .computeShader = "shaders/particles/particles_c.comp"
    };


    unsigned int vao = 0;
    unsigned int vbo = 0;

    unsigned int shaderProgram = 0;
    unsigned int computeProgram = 0;

    CommonUniforms uniforms;

    void initData();
    void updateUniforms();

};
