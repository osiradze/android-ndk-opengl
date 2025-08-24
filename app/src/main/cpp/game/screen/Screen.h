//
// Created by OSiradze on 22.08.25.
//

#pragma once

#include <string>

/**
 * Screen class create FrameBuffer and RenderBuffer, it saves screen texture
 */

class Screen {
public:
    Screen(int width, int height);
    void bind() const;
    void draw() const;
    void getPixel(int x, int y, uint8_t out[4]);
    void destroy();
    ~Screen();

private:
    // framebuffer
    int width; int height;
    unsigned int fbo = 0;
    unsigned int texture = 0;
    unsigned int rbo = 0;

    // drawing
    unsigned int vao = 0, vbo = 0, ebo = 0;
    std::string vertexShaderPath = "shaders/screen/screen_v.vert";
    std::string fragmentShaderPath = "shaders/screen/screen_f.frag";
    unsigned int shaderProgram = 0;
    int textureLocation = -1;

    void initScreenRect();
};