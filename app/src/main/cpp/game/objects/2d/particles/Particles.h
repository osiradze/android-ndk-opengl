//
// Created by OSiradze on 30.08.25.
//

#pragma once

#include "../../GameObject.h"
#include "../../shaders/Uniforms.h"
#include "../../shaders/ShadersPaths.h"
#include "ParticlesData.h"
#include "../../../environment/Environment.h"
#include "../../shaders/Program.h"
#include "../../../uievents/TouchDown.h"


class Particles: GameObject {
public:
    explicit Particles(
            Environment *env,
            GLObjectData* objectDataPtr,
            TouchDown* touchPosition
): env(env), data(std::make_unique<ParticlesData>(objectDataPtr)), objectDataPtr(objectDataPtr), touchPosition(touchPosition){}

    void init() override;
    void onDraw() override;
    void destroy() override;

private:
    Environment *env;
    std::unique_ptr<ParticlesData> data;
    GLObjectData* objectDataPtr;

    TouchDown* touchPosition;
    ShadersPaths shaders = {
            .vertexShader = "shaders/particles/particles_v.vert",
            .fragmentShader = "shaders/particles/particles_f.frag",
            .computeShader = "shaders/particles/particles_c.comp"
    };


    unsigned int vao = 0;
    unsigned int vbo = 0;

    Program shaderProgram;
    Program computeProgram;


    void initData();
    void updateUniforms();

};
