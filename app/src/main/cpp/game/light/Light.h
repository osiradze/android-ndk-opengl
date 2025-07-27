//
// Created by OSiradze on 27.07.25.
//

#pragma once

#include "glm/vec3.hpp"

class Light {
public:
    glm::vec3 light_position;
    glm::vec3 light_color;
    float light_intensity;

    Light(glm::vec3 light_position, glm::vec3 light_color, float light_intensity):
        light_position(light_position),
        light_color(light_color),
        light_intensity(light_intensity) {}

    void rotate(float angle, glm::vec3 vector);

    void setUniforms(int u_light_position, int u_light_color, int u_light_intensity) const;
};
