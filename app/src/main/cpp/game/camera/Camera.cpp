//
// Created by OSiradze on 23.07.25.
//
#include "Camera.h"
#include "../utils/MathUtils.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GLES3/gl3.h>

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, float fov, float ratio, float nearPlane, float farPlane)
        : eye(eye),
          center(center),
          up(up),
          fov(fov),
          ratio(ratio),
          nearPlane(nearPlane),
          farPlane(farPlane),
          view(lookAt(eye, center, up)),
          projection(glm::perspective(glm::radians(fov), ratio, nearPlane, farPlane))
{}

void Camera::setRatio(float r) {
    this->ratio = r;
    projection = glm::perspective(glm::radians(fov), ratio, nearPlane, farPlane);
}

void Camera::rotate(float angle, glm::vec3 vector) {
    eye = MathUtils::rotate(eye, angle, vector);
    view = glm::lookAt(eye, center, up);
}



void Camera::setUniform(
        CameraUniforms &uniforms
) {
    glUniformMatrix4fv(uniforms.u_view, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(uniforms.u_projection, 1, GL_FALSE, &projection[0][0]);
    glUniform3f(uniforms.u_camera_position, eye.x, eye.y, eye.z);
}

void Camera::zoom(float delta) {
    float distance = glm::length(eye - center);
    distance += delta;
    glm::vec3 direction = glm::normalize(eye - center);
    eye = center + direction * distance;
    view = glm::lookAt(eye, center, up);
}


