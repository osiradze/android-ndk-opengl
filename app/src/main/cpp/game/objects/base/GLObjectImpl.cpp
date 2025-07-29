//
// Created by OSiradze on 13.07.25.
//

#include <GLES3/gl3.h>
#include "GameObject.h"
#include "GLObject.h"
#include "GameObjectData.h"
#include "../../utils/OpenglUtils.h"
#include "../../camera/Camera.h"
#include "../../light/Light.h"
#include "../../environment/Environment.h"
#include <array>

#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/ext/matrix_transform.hpp"
#include "ShadersPaths.h"


class GLObjectImpl : public GameObject, private GLObject {

public:

    explicit GLObjectImpl(
            Environment* env,
            GLObjectData* data,
            ShadersPaths shaders
    ): env(env), data(data), shaders(shaders) {}

    void init() override {
        if (!data || !data->vertexData || !data->indices) return;
        if (!OpenglUtils::createProgram(program, shaders.vertexShader.c_str(), shaders.fragmentShader.c_str())) { return; }
        initUniforms();
        initData();
        initTexture();
    }

    void onDraw() override {
        if (!data || !data->vertexData || !data->indices) return;
        time++;
        glUseProgram(program);
        glBindVertexArray(vao);
        bindDrawUniforms();
        activateTextures();
        glDrawElements(GL_TRIANGLES, data->indicesCount, GL_UNSIGNED_INT, nullptr);
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

    int time = 0;
    Environment* env;
    GLObjectData* data;

    ShadersPaths shaders;


    static const unsigned int numberOfTextures = 3;
    unsigned int texture[numberOfTextures]{};
    int textureLocations[numberOfTextures]{};

    void initData() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data->vertexDataSize, data->vertexData.get(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data->stride, (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, data->stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, data->stride, (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, data->stride, (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(3);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->indicesSize, data->indices.get(), GL_STATIC_DRAW);

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

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        OpenglUtils::loadTexture("textures/texture3.png");
        textureLocations[2] = glGetUniformLocation(program, "u_texture_3");

        glUseProgram(program);
        glUniform1i(textureLocations[0], 0);                // assign sampler to texture unit 0
        glUniform1i(textureLocations[1], 1);                // assign sampler to texture unit 1
        glUniform1i(textureLocations[2], 2);                // assign sampler to texture unit 1
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
        glUniformMatrix4fv(uniforms.u_model, 1, GL_FALSE, &data->model[0][0]);
        env->camera.setUniform(uniforms.u_view, uniforms.u_projection, uniforms.u_camera_position);
        env->light.setUniforms(uniforms.u_light_position, uniforms.u_light_color, uniforms.u_light_intensity, uniforms.u_ambient_amount);
    }

};