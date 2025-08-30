//
// Created by OSiradze on 30.08.25.
//

#include "Particles.h"
#include "../../../utils/OpenglUtils.h"
#include "../../../utils/ShaderUtil.h"

void Particles::init() {
    if (!data || !data->data) return;

    // init programs
    if (!OpenglUtils::createProgram(shaderProgram, shaders.vertexShader.c_str(), shaders.fragmentShader.c_str())) { return; }
    if (!OpenglUtils::createComputeProgram(computeProgram, shaders.computeShader.c_str())) { return; }
    uniforms.init(shaderProgram);
    initData();
}

void Particles::initData() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data->dataSize, data->data.get(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data->stride, nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Particles::onDraw() {
   /* ShaderUtil::computeShader(computeProgram,[&]{

        },&vbo, 1,data->indicesCount,  1, 1
    );*/
    glUseProgram(shaderProgram);
    updateUniforms();
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, data->indicesCount);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Particles::destroy() {
    glBindVertexArray(0);
    glUseProgram(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(computeProgram);
}

void Particles::updateUniforms() {
    glUniformMatrix4fv(uniforms.camera.u_model, 1, GL_FALSE, &objectDataPtr->getTranslation()->getModel()[0][0]);
    env->camera.setUniform(uniforms.camera);

}

