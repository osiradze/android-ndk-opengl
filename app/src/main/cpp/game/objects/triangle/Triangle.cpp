//
// Created by OSiradze on 13.07.25.
//

#include "../GameObject.h"
#include "../../utils/OpenglUtils.h"
#include <GLES3/gl3.h>
#include <array>
#include <android/log.h>
#include "../GLObject.h"
#include "../uniform/Uniforms.h"

class Triangle : public GameObject, private GLObject {

public:
    void init() override {
        if (!OpenglUtils::createProgram(program, vertexPath, fragmentPath)) { return; }
        initUniforms();
        initData();
    }

    void onDraw() override {
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glUseProgram(0);
    }

private:

    CommonUniforms uniforms = {};
    // 4 vertices (x, y)
    const std::array<float, 8> vertexData = {
            -0.5f, -0.5f,  // bottom left
            0.5f, -0.5f,  // bottom right
            0.5f,  0.5f,  // top right
            -0.5f,  0.5f   // top left
    };
    unsigned int vertexDataSize = vertexData.size() * sizeof(float);

    // 6 indices (2 triangles)
    const std::array<unsigned int, 6> indices = {
            0, 1, 2,
            2, 3, 0
    };
    unsigned int indicesSize = indices.size() * sizeof(unsigned int);

    unsigned int numberOfFloatsPerVertex = 2; // x, y

    const char* vertexPath = "triangle_v.vert";
    const char* fragmentPath = "triangle_f.frag";

    void initData() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, numberOfFloatsPerVertex, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void initUniforms() {
        uniforms.u_ratio = glGetUniformLocation(program, "u_ratio");
        setRatio(1.0f);
    }

    void resize(int width, int height) override {
        float ratio = static_cast<float>(width) / static_cast<float>(height);
        setRatio(ratio);
    }

    void setRatio(float ratio) {
        glUseProgram(program);
        glUniform1f(uniforms.u_ratio, ratio);
        glUseProgram(0);
    }

};