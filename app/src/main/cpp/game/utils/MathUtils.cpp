//
// Created by OSiradze on 24.07.25.
//
#include "MathUtils.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

glm::vec3 MathUtils::rotate(glm::vec3 vector, float degree, glm::vec3 axis) {
    glm::vec3 normalizedAxis = glm::normalize(axis);

    // Convert degrees to radians
    float radians = glm::radians(degree);

    // Use glm::rotate from rotate_vector.hpp to rotate the vector
    return glm::rotate(vector, radians, normalizedAxis);
}

