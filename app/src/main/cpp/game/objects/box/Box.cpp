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
    const std::array<float, 64> vertexData = {
            // positions          // colors          // tex coords
            // 0
            -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
            // 1
            0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
            // 2
            0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
            // 3
            -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
            // 4
            -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f,
            // 5
            0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f,   1.0f, 0.0f,
            // 6
            0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
            // 7
            -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f
    };
    unsigned int vertexDataSize = vertexData.size() * sizeof(float);

    const std::array<unsigned int, 36> indices = {
            // back face
            0, 1, 2,
            2, 3, 0,
            // front face
            4, 5, 6,
            6, 7, 4,
            // left face
            0, 4, 7,
            7, 3, 0,
            // right face
            1, 5, 6,
            6, 2, 1,
            // bottom face
            0, 1, 5,
            5, 4, 0,
            // top face
            3, 2, 6,
            6, 7, 3
    };
    unsigned int indicesSize = indices.size() * sizeof(unsigned int);

    BoxData() {
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    };
};

class Box : public GameObject, private GLObject {

public:

    explicit Box(Camera* cameraPtr){
        camera = cameraPtr;
    }

    void init() override {
        if (!OpenglUtils::createProgram(program, vertexPath, fragmentPath)) { return; }
        initUniforms();
        initData();
        initTexture();
    }

    void onDraw() override {
        time++;
        data.model = glm::rotate(data.model, glm::radians(0.2f), glm::vec3(0.0f, 1.0f, 0.0f));
        //data.model = glm::rotate(data.model, glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f));

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

    const char* vertexPath = "shaders/triangle_v.vert";
    const char* fragmentPath = "shaders/triangle_f.frag";


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
        uniforms.u_ratio = glGetUniformLocation(program, "u_ratio");
        uniforms.u_time = glGetUniformLocation(program, "u_time");
        uniforms.u_model = glGetUniformLocation(program, "u_model");
        uniforms.u_view = glGetUniformLocation(program, "u_view");
        uniforms.u_projection = glGetUniformLocation(program, "u_projection");
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
        glUniformMatrix4fv(uniforms.u_view, 1, GL_FALSE, &camera->view[0][0]);
        glUniformMatrix4fv(uniforms.u_projection, 1, GL_FALSE, &camera->projection[0][0]);
    }

};