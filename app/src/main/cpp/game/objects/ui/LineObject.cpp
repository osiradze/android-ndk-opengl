//
// Created by OSiradze on 28.08.25.
//
#include <GLES3/gl31.h>
#include "LineObject.h"
#include "../../utils/OpenglUtils.h"
#include "../../utils/ShaderUtil.h"

void LineObject::init() {
    if (!data || !data->vertexData) return;

    // init programs
    if (!OpenglUtils::createProgram(shaderProgram, shaders.vertexShader.c_str(), shaders.fragmentShader.c_str())) { return; }
    if (!OpenglUtils::createComputeProgram(computeProgram, shaders.computeShader.c_str())) { return; }
    u_index = glGetUniformLocation(computeProgram, "u_index");
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
    glVertexAttribPointer(0, data->floatPerVertex, GL_FLOAT, GL_FALSE, data->stride, (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void LineObject::onDraw() {

    ShaderUtil::computeShader(computeProgram,[&]{
            glUniform1ui(u_index, index);
            glUniform2f(u_touch, touchPosition->floatX, touchPosition->floatY);
            glUniform1ui(u_vertex_number, data->indicesCount);
            if(touchPosition->active) {
                glUniform1i(u_mode, 2);
            } else {
                glUniform1i(u_mode, 3);
            }
            if(touchPosition->start) {
                glUniform1i(u_mode, 1);
            }
            //index++;
        },
        &vbo, 1,data->indicesCount,  1, 1
    );
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
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
