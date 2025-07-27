//
// Created by OSiradze on 13.07.25.
//

#include "glm/ext/matrix_float4x4.hpp"
#include "../uniform/Uniforms.h"

class GLObject {
protected:
    unsigned int program = 0;

    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;

    CommonUniforms uniforms = {};
};