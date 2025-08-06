//
// Created by OSiradze on 13.07.25.
//
#include <GLES3/gl3.h>
struct CommonUniforms {
    int u_ratio = -1;
    int u_model = -1;
    int u_view = -1;
    int u_projection = -1;

    int u_ambient_amount = -1;
    int u_light_position = -1;
    int u_light_color = -1;
    int u_light_intensity = -1;

    int u_camera_position = -1;

    int u_is_outline = -1;
public:
    void init(unsigned int program) {
        u_ratio = glGetUniformLocation(program, "u_ratio");
        u_model = glGetUniformLocation(program, "u_model");
        u_view = glGetUniformLocation(program, "u_view");
        u_projection = glGetUniformLocation(program, "u_projection");
        u_ambient_amount = glGetUniformLocation(program, "u_ambient_amount");
        u_light_position = glGetUniformLocation(program, "u_light_position");
        u_light_color = glGetUniformLocation(program, "u_light_color");
        u_light_intensity = glGetUniformLocation(program, "u_light_intensity");
        u_camera_position = glGetUniformLocation(program, "u_camera_position");
        u_is_outline = glGetUniformLocation(program, "u_is_outline");
    }
};