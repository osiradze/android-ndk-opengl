//
// Created by OSiradze on 27.07.25.
//
#include <GLES3/gl3.h>
#include "Light.h"
#include "../utils/MathUtils.h"
#include <glm/ext/matrix_transform.hpp>

void Light::setUniforms(int u_light_position, int u_light_color, int u_light_intensity) const {
    glUniform3f(u_light_position, light_position.x, light_position.y, light_position.z);
    glUniform3f(u_light_color, light_color.x, light_color.y, light_color.z);
    glUniform1f(u_light_intensity, light_intensity);
}

void Light::rotate(float angle, glm::vec3 vector) {
    light_position = MathUtils::rotate(light_position, glm::radians(angle), vector);
}

