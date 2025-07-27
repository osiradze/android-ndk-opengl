//
// Created by OSiradze on 23.07.25.
//
#pragma once

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
        unsigned int u_view,
        unsigned int u_projection,
        unsigned int u_camera_position
) {
    glUniformMatrix4fv(u_view, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(u_projection, 1, GL_FALSE, &projection[0][0]);
    glUniform3f(u_camera_position, eye.x, eye.y, eye.z);
}


