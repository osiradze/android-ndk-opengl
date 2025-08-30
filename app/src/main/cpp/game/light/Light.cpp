//
// Created by OSiradze on 27.07.25.
//
#include <GLES3/gl31.h>
#include "Light.h"
#include "../utils/MathUtils.h"
#include <glm/ext/matrix_transform.hpp>


void Light::setUniforms(
        LightUniforms &uniforms
) const {
        glUniform3f(uniforms.u_light_position, light_position.x, light_position.y,light_position.z);
        glUniform3f(uniforms.u_light_color, light_color.x, light_color.y, light_color.z);
        glUniform1f(uniforms.u_light_intensity, light_intensity);
        glUniform1f(uniforms.u_ambient_amount, ambient_amount);
        glUniform1f(uniforms.u_light_constant, light_attenuation.constant);
        glUniform1f(uniforms.u_light_linear, light_attenuation.linear);
        glUniform1f(uniforms.u_light_quadratic, light_attenuation.quadratic);

}

void Light::rotate(float angle, glm::vec3 vector) {
    light_position = MathUtils::rotate(light_position, glm::radians(angle), vector);
}