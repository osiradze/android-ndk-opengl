//
// Created by OSiradze on 23.07.25.
//
#pragma once

#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

Camera::Camera(glm::vec3 position, float fov, float ratio, float nearPlane, float farPlane) {
    this->fov = fov;
    this->ratio = ratio;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
    view = glm::translate(view, position);
    projection = glm::perspective(glm::radians(fov), ratio, nearPlane, farPlane);
}

void Camera::setRatio(float r) {
    this->ratio = r;
    projection = glm::perspective(glm::radians(fov), ratio, nearPlane, farPlane);
}
