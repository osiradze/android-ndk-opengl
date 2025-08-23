//
// Created by OSiradze on 22.08.25.
//

#pragma once

/**
 * Screen class create FrameBuffer and RenderBuffer, it saves screen texture
 */

class Screen {
public:
    int width; int height;
    unsigned int fbo = 0;
    unsigned int texture = 0;
    unsigned int rbo = 0;

    Screen(int width, int height);
    void bind();
    void draw();
    void destroy();
    ~Screen();
};