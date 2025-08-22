//
// Created by OSiradze on 22.08.25.
//

#pragma

/**
 * Screen class create FrameBuffer and RenderBuffer, it saves screen texture
 */

class Screen {
public:
    int width; int height;
    unsigned int fbo;
    unsigned int texture;
    unsigned int rbo;

    Screen(int width, int height);
    void bind();
    void draw();
    void destroy();
    ~Screen();
};