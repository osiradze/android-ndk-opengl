//
// Created by OSiradze on 23.07.25.
//
#pragma once

#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <GLES3/gl3.h>

using namespace glm;

Camera::Camera(vec3 eye, vec3 center, vec3 up, float fov, float ratio, float nearPlane, float farPlane)
        : eye(eye),
          center(center),
          up(up),
          fov(fov),
          ratio(ratio),
          nearPlane(nearPlane),
          farPlane(farPlane),
          view(lookAt(eye, center, up)),
          projection(perspective(radians(fov), ratio, nearPlane, farPlane))
{}

void Camera::setRatio(float r) {
    this->ratio = r;
    projection = perspective(radians(fov), ratio, nearPlane, farPlane);
}

void Camera::setUniform(unsigned int u_view, unsigned int u_projection) {
    glUniformMatrix4fv(u_view, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(u_projection, 1, GL_FALSE, &projection[0][0]);
}
