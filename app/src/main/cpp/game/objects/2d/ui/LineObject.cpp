//
// Created by OSiradze on 28.08.25.
//
#include <GLES3/gl31.h>
#include "LineObject.h"
#include "../../../utils/OpenglUtils.h"
#include "../../../utils/ShaderUtil.h"

void LineObject::init() {
    if (!data || !data->vertexData) return;

    // init programs
    if (!OpenglUtils::createProgram(shaderProgram, shaders.vertexShader.c_str(), shaders.fragmentShader.c_str())) { return; }
    if (!OpenglUtils::createComputeProgram(computeProgram, shaders.computeShader.c_str())) { return; }
    u_touch = glGetUniformLocation(computeProgram, "u_touch");
    u_mode = glGetUniformLocation(computeProgram, "u_mode");
    u_vertex_number = glGetUniformLocation(computeProgram, "u_vertex_number");

    initData();
}

void LineObject::initData() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data->vertexDataSize, data->vertexData.get(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, data->floatPerVertex, GL_FLOAT, GL_FALSE, data->stride, nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void LineObject::onDraw() {
    if(!touchPosition->active) return;
    ShaderUtil::computeShader(computeProgram,[&]{
            glUniform2f(u_touch, touchPosition->floatX, touchPosition->floatY);
            glUniform1ui(u_vertex_number, data->indicesCount);

            glUniform1i(u_mode, 2);
            if(touchPosition->start) {
                glUniform1i(u_mode, 1);
            }
        },
        &vbo, 1,data->indicesCount,  1, 1
    );
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    //glLineWidth(30.0f);
    glDrawArrays(GL_LINE_STRIP, 0, data->indicesCount);
    glBindVertexArray(0);
    glUseProgram(0);
}

void LineObject::destroy() {
    glBindVertexArray(0);
    glUseProgram(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(computeProgram);
}
