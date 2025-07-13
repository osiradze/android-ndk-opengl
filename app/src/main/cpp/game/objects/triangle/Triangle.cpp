//
// Created by OSiradze on 13.07.25.
//

#include "../GameObject.h"
#include "../../utils/OpenglUtils.h"
#include <GLES3/gl3.h>
#include <array>
#include <android/log.h>

class Triangle : public GameObject {

public:
    void init() override {
        if (!loadProgram()) { return; }
        initUniforms();
        initVao();
    }

    void onDraw() override {
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, boxIndices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glUseProgram(0);
    }

private:

    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;

    unsigned int program = 0;

    // 4 vertices (x, y)
    const std::array<float, 8> vertexData = {
            -0.5f, -0.5f,  // bottom left
            0.5f, -0.5f,  // bottom right
            0.5f,  0.5f,  // top right
            -0.5f,  0.5f   // top left
    };

    int stride = 2 * sizeof(float); // 2 floats per vertex (x, y)
    int numberOfFloatsPerVertex = 2;

    // 6 indices (2 triangles)
    const std::array<unsigned int, 6> boxIndices = {
            0, 1, 2,
            2, 3, 0
    };

    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    int u_ratio;


    void initShaderSources() {
        vertexShaderSource = OpenglUtils::loadShaderFromFile("triangle_v.vert");
        fragmentShaderSource = OpenglUtils::loadShaderFromFile("triangle_f.frag");
    }

    bool loadProgram() {
        initShaderSources();
        unsigned int vertexShader, fragmentShader;
        if(!OpenglUtils::createShader(GL_VERTEX_SHADER, vertexShaderSource.c_str(), vertexShader)) {
            return false;
        }
        if(!OpenglUtils::createShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str(), fragmentShader)){
            return false;
        }
        auto success = OpenglUtils::createProgram(vertexShader, fragmentShader, program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        __android_log_print(ANDROID_LOG_INFO, "GameTag", "Program created successfully: %d", success);
        return success;
    }

    void initVao() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, numberOfFloatsPerVertex, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, boxIndices.size() * sizeof(unsigned int), boxIndices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void initUniforms() {
        u_ratio = glGetUniformLocation(program, "u_ratio");
        setRatio(1.0f);
    }

    void resize(int width, int height) override {
        float ratio = static_cast<float>(width) / static_cast<float>(height);
        setRatio(ratio);
    }

    void setRatio(float ratio) {
        glUseProgram(program);
        glUniform1f(u_ratio, ratio);
        glUseProgram(0);
    }

};