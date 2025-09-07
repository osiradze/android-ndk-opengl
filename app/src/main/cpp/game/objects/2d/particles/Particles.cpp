//
// Created by OSiradze on 30.08.25.
//

#include "Particles.h"
#include "../../../utils/OpenglUtils.h"
#include "../../../utils/ShaderUtil.h"

void Particles::init() {
    if (!data || !data->data) return;

    // init programs
    if (!OpenglUtils::createProgram(shaderProgram.id, shaders.vertexShader.c_str(), shaders.fragmentShader.c_str())) { return; }
    OpenglUtils::createComputeProgram(computeProgram.id, shaders.computeShader.c_str());
    shaderProgram.uniforms.init(shaderProgram.id);
    computeProgram.uniforms.init(computeProgram.id);
    initData();
}

void Particles::initData() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data->dataSize, data->data.get(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data->stride, nullptr);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, data->stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Particles::onDraw() {
    updateUniforms();
    ShaderUtil::computeShader(computeProgram.id,[&]{
        if(touchPosition->active) {
            glUniform2f(computeProgram.uniforms.ui.u_touch_position, touchPosition->floatX,
                        touchPosition->floatY);
        }
        glUniform1ui(computeProgram.uniforms.ui.u_touch_is_active, touchPosition->active);
        },&vbo, 1,data->indicesCount,  1, 1
    );
    glUseProgram(shaderProgram.id);
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
    glDeleteProgram(shaderProgram.id);
    glDeleteProgram(computeProgram.id);
}

void Particles::updateUniforms() {
    glUseProgram(shaderProgram.id);
    glUniformMatrix4fv(shaderProgram.uniforms.camera.u_model, 1, GL_FALSE, &objectDataPtr->getTranslation()->getModel()[0][0]);
    env->camera.setUniform(shaderProgram.uniforms.camera);
    glUseProgram(computeProgram.id);
    glUniformMatrix4fv(computeProgram.uniforms.camera.u_model, 1, GL_FALSE, &objectDataPtr->getTranslation()->getModel()[0][0]);
    env->camera.setUniform(computeProgram.uniforms.camera);

}

