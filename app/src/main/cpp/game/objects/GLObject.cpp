//
// Created by OSiradze on 13.07.25.
//

#include <GLES3/gl3.h>
#include "base/GameObject.h"
#include "base/GameObjectData.h"
#include "../utils/OpenglUtils.h"
#include "../camera/Camera.h"
#include "../light/Light.h"
#include "../environment/Environment.h"
#include <array>
#include <utility>
#include <android/log.h>

#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/ext/matrix_transform.hpp"
#include "base/ShadersPaths.h"
#include "texture/Texture.h"
#include "GLObject.h"

void GLObject::init() {
    if (!data || !data->vertexData || !data->indices) return;

    // init programs
    if (!OpenglUtils::createProgram(shaderProgram.id, shaders.vertexShader.c_str(),
                                    shaders.fragmentShader.c_str())) { return; }
    OpenglUtils::createProgram(stencilProgram.id, shaders.vertexShader.c_str(),
                               shaders.stencilFragmentShader.c_str());

    OpenglUtils::createProgram(colorIdProgram.id, shaders.vertexShader.c_str(),
                               shaders.colorIdFragmentShader.c_str());


    initUniforms();
    initData();
    initTexture();
}

void GLObject::onDraw() {
    Program &programToUse = env->colorIdMode ? colorIdProgram : shaderProgram;
    glUseProgram(programToUse.id);
    glBindVertexArray(vao);
    updateUniforms(programToUse);
    activateTextures();
    setUpDrawStencil();
    glDrawElements(GL_TRIANGLES, data->indicesCount, GL_UNSIGNED_INT, nullptr);
    drawOutLine();
    glBindVertexArray(0);
    glUseProgram(0);
}

void GLObject::destroy() {
    glBindVertexArray(0);
    glUseProgram(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shaderProgram.id);
    glDeleteProgram(stencilProgram.id);
    glDeleteProgram(colorIdProgram.id);
    glDeleteTextures(2, texture);
}

void GLObject::initData() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data->vertexDataSize, data->vertexData.get(), GL_STATIC_DRAW);

    // vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data->stride, (void *) 0);
    glEnableVertexAttribArray(0);

    // normal attributes
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, data->stride, (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coordinate attributes
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, data->stride, (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // color attributes
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, data->stride, (void *) (8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->indicesSize, data->indices.get(),
                 GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLObject::initTexture() {
    if (!texturePath.has_value()) {
        return;
    }
    glGenTextures(numberOfTextures, texture);
    glActiveTexture(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    OpenglUtils::loadTexture(texturePath->diffuse.c_str());
    textureLocations[0] = glGetUniformLocation(shaderProgram.id, "u_texture");

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    OpenglUtils::loadTexture(texturePath->specular.c_str());
    textureLocations[1] = glGetUniformLocation(shaderProgram.id, "u_texture_specular");

    glUseProgram(shaderProgram.id);
    glUniform1i(textureLocations[0], 0);                // assign sampler to texture unit 0
    glUniform1i(textureLocations[1], 1);                // assign sampler to texture unit 1
    glUseProgram(0);
}

void GLObject::initUniforms() {
    shaderProgram.uniforms.init(shaderProgram.id, env->lights.size());
    stencilProgram.uniforms.init(stencilProgram.id);
    colorIdProgram.uniforms.init(colorIdProgram.id);
}

void GLObject::activateTextures() {
    if (!texturePath.has_value()) {
        return;
    }
    for (int i = 0; i < numberOfTextures; ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texture[i]);
    }
}

void GLObject::updateUniforms(Program &program) {
    glUniformMatrix4fv(program.uniforms.camera.u_model, 1, GL_FALSE, &data->getTranslation()->getModel()[0][0]);
    env->camera.setUniform(program.uniforms.camera);
    glUniform1i(program.uniforms.number_of_lights, program.uniforms.light.size());
    for (int i = 0; i < program.uniforms.light.size(); i++) {
        env->lights[i].setUniforms(program.uniforms.light[i]);
    }

    // for color id
    glUniform3f(program.uniforms.u_color_id, data->colorId[0], data->colorId[1], data->colorId[2]);

}

void GLObject::setUpDrawStencil() const {
    if (!data->outline || env->colorIdMode) return;
    glStencilFunc(GL_ALWAYS, 1, 0xFF); // draw object fully in stencil buffer
    glStencilMask(0xFF); // enable writing to the stencil buffer
    glStencilOp(GL_KEEP, GL_KEEP,GL_REPLACE); // replace stencil then depth and stencil test passes
}

void GLObject::drawOutLine() {
    if (!data->outline || env->colorIdMode) return;
    glStencilMask(0x00); // don't write in stencil buffer
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // draw only where stencil is not equal to 1

    glUseProgram(stencilProgram.id);
    glm::vec3 scale = data->getTranslation()->getScale();
    data->getTranslation()->setScale(scale * 1.01f); // scale up for outline effect
    updateUniforms(stencilProgram);
    glDrawElements(GL_TRIANGLES, data->indicesCount, GL_UNSIGNED_INT, nullptr);
    data->getTranslation()->setScale(scale);

    glStencilFunc(GL_ALWAYS, 1, 0xFF); // reset stencil function
    glStencilMask(0xFF);
}
