//
// Created by OSiradze on 13.07.25.
//

#include <GLES3/gl3.h>
#include "base/GameObject.h"
#include "base/GLObject.h"
#include "base/GameObjectData.h"
#include "../utils/OpenglUtils.h"
#include "../camera/Camera.h"
#include "../light/Light.h"
#include "../environment/Environment.h"
#include <array>

#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/ext/matrix_transform.hpp"
#include "base/ShadersPaths.h"
#include "texture/Texture.h"


class GLObjectImpl : public GameObject, private GLObject {

public:

    explicit GLObjectImpl(
            Environment* env,
            GLObjectData* data,
            ShadersPaths shaders,
            Texture texturePath = Texture()
    ): env(env), data(data), shaders(shaders), texturePath(texturePath) {}

    void init() override {
        if (!data || !data->vertexData || !data->indices) return;
        if (!OpenglUtils::createProgram(program, shaders.vertexShader.c_str(), shaders.fragmentShader.c_str())) { return; }
        initUniforms();
        initData();
        initTexture();
    }

    void onDraw() override {
        if (!data || !data->vertexData || !data->indices) return;
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
    Environment* env;
    GLObjectData* data;

    ShadersPaths shaders;



    static const unsigned int numberOfTextures = 2;
    unsigned int texture[numberOfTextures]{};
    int textureLocations[numberOfTextures]{};
    Texture texturePath = Texture();

    void initData() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data->vertexDataSize, data->vertexData.get(), GL_STATIC_DRAW);

        // vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data->stride, (void*)0);
        glEnableVertexAttribArray(0);

        // normal attributes
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, data->stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // texture coordinate attributes
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, data->stride, (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // color attributes
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
        glActiveTexture(GL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        OpenglUtils::loadTexture(texturePath.diffuse.c_str());
        textureLocations[0] = glGetUniformLocation(program, "u_texture");

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        OpenglUtils::loadTexture(texturePath.specular.c_str());
        textureLocations[1] = glGetUniformLocation(program, "u_texture_specular");

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
        glUniformMatrix4fv(uniforms.u_model, 1, GL_FALSE, &data->model[0][0]);
        env->camera.setUniform(uniforms.u_view, uniforms.u_projection, uniforms.u_camera_position);
        env->light.setUniforms(uniforms.u_light_position, uniforms.u_light_color, uniforms.u_light_intensity, uniforms.u_ambient_amount);
    }

};