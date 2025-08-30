//
// Created by OSiradze on 13.07.25.
//

#pragma once
#include <GLES3/gl31.h>
#include <string>
#include <vector>

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
    void init(unsigned int program, int lightIndex) {
        u_ambient_amount = glGetUniformLocation(program, ("u_light[" + std::to_string(lightIndex) + "].ambient_amount").c_str());
        u_light_position = glGetUniformLocation(program, ("u_light[" + std::to_string(lightIndex) + "].position").c_str());
        u_light_color = glGetUniformLocation(program, ("u_light[" + std::to_string(lightIndex) + "].color").c_str());
        u_light_intensity = glGetUniformLocation(program, ("u_light[" + std::to_string(lightIndex) + "].intensity").c_str());
        u_light_constant = glGetUniformLocation(program, ("u_light[" + std::to_string(lightIndex) + "].constant").c_str());
        u_light_linear = glGetUniformLocation(program, ("u_light[" + std::to_string(lightIndex) + "].linear").c_str());
        u_light_quadratic = glGetUniformLocation(program, ("u_light[" + std::to_string(lightIndex) + "].quadratic").c_str());
    }
};

struct CommonUniforms {
    CameraUniforms camera;
    std::vector<LightUniforms> light;
    int number_of_lights = -1;
    int u_color_id = -1;
public:
    void init(unsigned int program, int lightCount = 0) {
        light = std::vector<LightUniforms>(lightCount);
        for (int i = 0; i < light.size(); i++) {
            light[i].init(program, i);
        }
        number_of_lights = glGetUniformLocation(program, "u_number_of_lights");
        u_color_id = glGetUniformLocation(program, "u_color_id");
        camera.init(program);
    }
};