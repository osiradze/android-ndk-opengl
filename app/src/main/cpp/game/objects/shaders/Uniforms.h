//
// Created by OSiradze on 13.07.25.
//

#pragma once
#include <GLES3/gl3.h>

struct CameraUniforms {
    int u_ratio = -1;
    int u_model = -1;
    int u_view = -1;
    int u_projection = -1;
    int u_camera_position = -1;

    public:
    void init(unsigned int program) {
        u_ratio = glGetUniformLocation(program, "u_ratio");
        u_model = glGetUniformLocation(program, "u_model");
        u_view = glGetUniformLocation(program, "u_view");
        u_projection = glGetUniformLocation(program, "u_projection");
        u_camera_position = glGetUniformLocation(program, "u_camera_position");
    }
};

struct LightUniforms {
    int u_ambient_amount = -1;
    int u_light_position = -1;
    int u_light_color = -1;
    int u_light_intensity = -1;
    int u_light_constant = -1;
    int u_light_linear = -1;
    int u_light_quadratic = -1;

public:
    void init(unsigned int program) {
        u_ambient_amount = glGetUniformLocation(program, "u_light.ambient_amount");
        u_light_position = glGetUniformLocation(program, "u_light.position");
        u_light_color = glGetUniformLocation(program, "u_light.color");
        u_light_intensity = glGetUniformLocation(program, "u_light.intensity");
        u_light_constant = glGetUniformLocation(program, "u_light.constant");
        u_light_linear = glGetUniformLocation(program, "u_light.linear");
        u_light_quadratic = glGetUniformLocation(program, "u_light.quadratic");
    }
};

struct CommonUniforms {
    CameraUniforms camera;
    LightUniforms light;
public:
    void init(unsigned int program) {
        light.init(program);
        camera.init(program);
    }
};