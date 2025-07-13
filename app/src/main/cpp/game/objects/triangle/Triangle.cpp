//
// Created by OSiradze on 13.07.25.
//

#include <GLES3/gl3.h>
#include "../GameObject.h"
#include "../GLObject.h"
#include "../../utils/OpenglUtils.h"
#include "../uniform/Uniforms.h"
#include "../../../image/stb_image.h"
#include <array>
#include <android/log.h>

class Triangle : public GameObject, private GLObject {

public:
    void init() override {
        if (!OpenglUtils::createProgram(program, vertexPath, fragmentPath)) { return; }
        initUniforms();
        initData();
        initTexture();
    }

    void onDraw() override {
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
        glUseProgram(0);
    }

    void destroy() override {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteProgram(program);
        glDeleteTextures(1, &texture);
    }

private:

    CommonUniforms uniforms = {};
    unsigned int numberOfFloatsPerVertex = 8;
    unsigned int stride = numberOfFloatsPerVertex * sizeof(float);
    const std::array<float, 32> vertexData = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int vertexDataSize = vertexData.size() * sizeof(float);

    // 6 indices (2 triangles)
    const std::array<unsigned int, 6> indices = {
            0, 1, 2,
            2, 3, 0
    };
    unsigned int indicesSize = indices.size() * sizeof(unsigned int);

    const char* vertexPath = "shaders/triangle_v.vert";
    const char* fragmentPath = "shaders/triangle_f.frag";


    unsigned int texture = 0;

    void initData() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void initTexture() {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int w, h, ch;
        unsigned char* data = OpenglUtils::loadImageFromAssets("textures/texture.png", w, h, ch);

        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }else {
            __android_log_print(ANDROID_LOG_ERROR, "Triangle", "Failed to load texture");
        }
        stbi_image_free(data);
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