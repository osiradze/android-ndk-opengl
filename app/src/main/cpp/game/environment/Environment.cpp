//
// Created by OSiradze on 27.07.25.
//

#include "Environment.h"


Environment::Environment():
    camera(Camera::createDefaultCamera()),
    light(
            Light(
        glm::vec3(2.0f, 2.5f, 2.0f),
        glm::vec3(0.7f, 0.5f, 1.0f),
        2.0f,
        0.3f
        )
    )
{}

