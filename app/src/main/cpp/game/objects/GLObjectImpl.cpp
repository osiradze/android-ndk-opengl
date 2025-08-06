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
#include <utility>

#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/ext/matrix_transform.hpp"
#include "base/ShadersPaths.h"
#include "texture/Texture.h"


class GLObjectImpl : public GameObject, private GLObject {

public:

    explicit GLObjectImpl(
            Environment *env,
            GLObjectData *data,
            ShadersPaths shaders,
            std::optional<Texture> texturePath,
            bool outline = false
    )
            : env(env), data(data), shaders(std::move(shaders)),
              texturePath(std::move(texturePath)), outline(outline) {}

    void init() override {
        if (!data || !data->vertexData || !data->indices) return;

        // init programs
        if (!OpenglUtils::createProgram(shaderProgram.id, shaders.vertexShader.c_str(),
                                        shaders.fragmentShader.c_str())) { return; }
        OpenglUtils::createProgram(stencilProgram.id, shaders.vertexShader.c_str(),
                                   shaders.stencilFragmentShader.c_str());

        initUniforms();
        initData();
        initTexture();
    }

    void onDraw() override {
        if (!data || !data->vertexData || !data->indices) return;
        glUseProgram(shaderProgram.id);
        glBindVertexArray(vao);
        updateUniforms(shaderProgram);
        activateTextures();
        setUpDrawStencil();
        glDrawElements(GL_TRIANGLES, data->indicesCount, GL_UNSIGNED_INT, nullptr);
        drawOutLine();
        glBindVertexArray(0);
        glUseProgram(0);
    }

    void destroy() override {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteProgram(shaderProgram.id);
        glDeleteProgram(stencilProgram.id);
        glDeleteTextures(2, texture);
    }

private:
    Environment *env;
    GLObjectData *data;
    ShadersPaths shaders;

    std::optional<Texture> texturePath;
    static const unsigned int numberOfTextures = 2;
    unsigned int texture[numberOfTextures]{};
    int textureLocations[numberOfTextures]{};

    bool outline = false;

    void initData() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data->vertexDataSize, data->vertexData.get(), GL_STATIC_DRAW);

        // vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data->stride, (void *) 0);
        glEnableVertexAttribArray(0);

        // normal attributes
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, data->stride, (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // texture coordinate attributes
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, data->stride, (void *) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // color attributes
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, data->stride, (void *) (8 * sizeof(float)));
        glEnableVertexAttribArray(3);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data->indicesSize, data->indices.get(),
                     GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void initTexture() {
        if (!texturePath.has_value()) {
            return;
        }
        glGenTextures(numberOfTextures, texture);
        glActiveTexture(GL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        OpenglUtils::loadTexture(texturePath->diffuse.c_str());
        textureLocations[0] = glGetUniformLocation(shaderProgram.id, "u_texture");

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        OpenglUtils::loadTexture(texturePath->specular.c_str());
        textureLocations[1] = glGetUniformLocation(shaderProgram.id, "u_texture_specular");

        glUseProgram(shaderProgram.id);
        glUniform1i(textureLocations[0], 0);                // assign sampler to texture unit 0
        glUniform1i(textureLocations[1], 1);                // assign sampler to texture unit 1
        glUseProgram(0);
    }

    void initUniforms() {
        shaderProgram.uniforms.init(shaderProgram.id);
        stencilProgram.uniforms.init(stencilProgram.id);
        setRatio(1.0f);
    }

    void resize(int width, int height) override {
        float ratio = static_cast<float>(width) / static_cast<float>(height);
        setRatio(ratio);
    }

    void setRatio(float ratio) {
        glUseProgram(shaderProgram.id);
        glUniform1f(shaderProgram.uniforms.u_ratio, ratio);
        glUniform1f(stencilProgram.uniforms.u_ratio, ratio);
        glUseProgram(0);
    }

    void activateTextures() {
        if (!texturePath.has_value()) {
            return;
        }
        for (int i = 0; i < numberOfTextures; ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, texture[i]);
        }
    }

    void updateUniforms(Program &program) {
        glUniformMatrix4fv(program.uniforms.u_model, 1, GL_FALSE, &data->getTranslation()->getModel()[0][0]);
        env->camera.setUniform(program.uniforms.u_view, program.uniforms.u_projection, program.uniforms.u_camera_position);
        env->light.setUniforms(program.uniforms.u_light_position, program.uniforms.u_light_color,
                               program.uniforms.u_light_intensity, program.uniforms.u_ambient_amount);
    }

    void setUpDrawStencil() const {
        if (!outline) return;
        glStencilFunc(GL_ALWAYS, 1, 0xFF); // draw object fully in stencil buffer
        glStencilMask(0xFF); // enable writing to the stencil buffer
        glStencilOp(GL_KEEP, GL_KEEP,
                    GL_REPLACE); // replace stencil then depth and stencil test passes
    }

    void drawOutLine() {
        if (!outline) return;
        glStencilMask(0x00); // don't write in stencil buffer
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // draw only where stencil is not equal to 1

        glUseProgram(stencilProgram.id);
        data->getTranslation()->setScale(glm::vec3(1.01));
        updateUniforms(stencilProgram);
        glDrawElements(GL_TRIANGLES, data->indicesCount, GL_UNSIGNED_INT, nullptr);
        data->getTranslation()->setScale(glm::vec3(1.0));

        glStencilFunc(GL_ALWAYS, 1, 0xFF); // reset stencil function
        glStencilMask(0xFF);
    }
};