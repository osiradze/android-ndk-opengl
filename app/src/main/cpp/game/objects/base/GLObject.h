//
// Created by OSiradze on 13.07.25.
//

#include "glm/ext/matrix_float4x4.hpp"
#include "../shaders/Program.h"

class GLObject {
protected:
    Program shaderProgram;
    Program stencilProgram;

    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;
};