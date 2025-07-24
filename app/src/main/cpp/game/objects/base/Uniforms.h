//
// Created by OSiradze on 13.07.25.
//
#include <GLES3/gl3.h>
struct CommonUniforms {
    int u_ratio = -1;
    int u_time = -1;
    int u_model = -1;
    int u_view = -1;
    int u_projection = -1;

public:
    void init(unsigned int program) {
        u_ratio = glGetUniformLocation(program, "u_ratio");
        u_time = glGetUniformLocation(program, "u_time");
        u_model = glGetUniformLocation(program, "u_model");
        u_view = glGetUniformLocation(program, "u_view");
        u_projection = glGetUniformLocation(program, "u_projection");
    }
};