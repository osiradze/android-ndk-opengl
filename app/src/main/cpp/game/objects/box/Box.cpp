//
// Created by OSiradze on 13.07.25.
//

#include <GLES3/gl3.h>
#include "../GameObject.h"
#include "../GLObject.h"
#include "../../utils/OpenglUtils.h"
#include "../../camera/Camera.h"
#include <array>

#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp>

struct BoxData {
    glm::mat4 model = glm::mat4(1.0f);

    unsigned int numberOfFloatsPerVertex = 8;
    unsigned int stride = numberOfFloatsPerVertex * sizeof(float);
    const std::array<float, 192> vertexData = {
            // Back face (z = -0.5)
            -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // bottom-left
            0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // bottom-right
            0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,  // top-right
            -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top-left

            // Front face (z = 0.5)
            -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // bottom-left
            0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,   1.0f, 0.0f,  // bottom-right
            0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,  // top-right
            -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,  // top-left

            // Left face (x = -0.5)
            -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // bottom-left
            -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,   1.0f, 0.0f,  // bottom-right
            -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,  // top-right
            -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top-left

            // Right face (x = 0.5)
            0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,  // bottom-left
            0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,   1.0f, 0.0f,  // bottom-right
            0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,  // top-right
            0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  // top-left

            // Bottom face (y = -0.5)
            -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // bottom-left
            0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // bottom-right
            0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,   1.0f, 1.0f,  // top-right
            -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,   0.0f, 1.0f,  // top-left

            // Top face (y = 0.5)
            -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f,  // bottom-left
            0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,  // bottom-right
            0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,  // top-right
            -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f   // top-left
    };

    const std::array<unsigned int, 36> indices = {
            // Back face
            0, 1, 2,   2, 3, 0,
            // Front face
            4, 5, 6,   6, 7, 4,
            // Left face
            8, 9, 10,  10, 11, 8,
            // Right face
            12, 13, 14, 14, 15, 12,
            // Bottom face
            16, 17, 18, 18, 19, 16,
            // Top face
            20, 21, 22, 22, 23, 20
    };
    unsigned int vertexDataSize = vertexData.size() * sizeof(float);
    unsigned int indicesSize = indices.size() * sizeof(unsigned int);
};

class Box : public GameObject, private GLObject {

public:

    explicit Box(
            Camera* cameraPtr,
            glm::mat4 model
    ){
        camera = cameraPtr;
        data.model = model;
    }

    void init() override {
        if (!OpenglUtils::createProgram(program, vertexPath, fragmentPath)) { return; }
        initUniforms();
        initData();
        initTexture();
    }

    void onDraw() override {
        time++;

        glUseProgram(program);
        glBindVertexArray(vao);
        bindDrawUniforms();
        activateTextures();
        glDrawElements(GL_TRIANGLES, data.indices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
        glUseProgram(0);
    }

    void destroy() override {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteProgram(program);
        glDeleteTextures(2, texture);
    }

private:

    int time = 0; // TODO needs export
    Camera* camera = nullptr;
    BoxData data;

    const char* vertexPath = "shaders/object_v.vert";
    const char* fragmentPath = "shaders/object_f.frag";


    static const unsigned int numberOfTextures = 2;
    unsigned int texture[numberOfTextures]{};
    int textureLocations[numberOfTextures]{};

    void initData() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.vertexDataSize, data.vertexData.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data.stride, (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, data.stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, data.stride, (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indicesSize, data.indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void initTexture() {
        glGenTextures(numberOfTextures, texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        textureLocations[0] = glGetUniformLocation(program, "u_texture_1");

        OpenglUtils::loadTexture("textures/texture1.png");
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        OpenglUtils::loadTexture("textures/texture2.png");
        textureLocations[1] = glGetUniformLocation(program, "u_texture_2");

        glUseProgram(program);
        glUniform1i(textureLocations[0], 0);                // assign sampler to texture unit 0
        glUniform1i(textureLocations[1], 1);                // assign sampler to texture unit 1
        glUseProgram(0);
    }

    void initUniforms() {
        uniforms.init(program);
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

    void activateTextures() {
        for (int i = 0; i < numberOfTextures; ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, texture[i]);
        }
    }
    void bindDrawUniforms() const {
        glUniform1i(uniforms.u_time, time);
        glUniformMatrix4fv(uniforms.u_model, 1, GL_FALSE, &data.model[0][0]);
        camera->setUniform(uniforms.u_view, uniforms.u_projection);
    }

};