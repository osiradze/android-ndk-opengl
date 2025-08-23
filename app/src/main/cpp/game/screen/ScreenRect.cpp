//
// Created by OSiradze on 22.08.25.
//
#include "Screen.h"
#include "../utils/OpenglUtils.h"
#include <GLES3/gl3.h>
#include <android/log.h>


void Screen::initScreenRect() {
    if (!OpenglUtils::createProgram(shaderProgram, vertexShaderPath.c_str(),fragmentShaderPath.c_str())) { return; }

    int stride = 4 * sizeof(float);
    float vertices[] = {
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f, 1.0f  // top-right
    };
    unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, nullptr);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    textureLocation = glGetUniformLocation(shaderProgram, "u_screen_texture");
    glBindTexture(GL_TEXTURE_2D, texture);
}