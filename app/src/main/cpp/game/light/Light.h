//
// Created by OSiradze on 27.07.25.
//

#pragma once

#include "glm/vec3.hpp"
#include "../objects/shaders/Uniforms.h"
#include "Attenuation.h"
#include <vector>

class Light {
public:
    glm::vec3 light_position;
    glm::vec3 light_color;
    float light_intensity;
    float ambient_amount;
    Attenuation light_attenuation;

    Light(glm::vec3 light_position,
          glm::vec3 light_color,
          float light_intensity,
          float ambient_amount,
          float light_distance):
        light_position(light_position),
        light_color(light_color),
        light_intensity(light_intensity),
        ambient_amount(ambient_amount),
        light_attenuation(Attenuation::getNearestAttenuation(light_distance)){}

    void rotate(float angle, glm::vec3 vector);

    void setUniforms(LightUniforms &uniforms) const;
};
