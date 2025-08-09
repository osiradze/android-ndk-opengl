//
// Created by OSiradze on 27.07.25.
//

#include "Environment.h"


Environment::Environment():
        camera(
            Camera(glm::vec3(4.0f, 4.0f, 4.0f),
                   glm::vec3(0.0f, 0.0f, 0.0f),
                   glm::vec3(0.0f, 1.0f, 0.0f),
                   50.0f,
                   1.0f,
                   0.1f,
                   100.0f)
            ),
        lights(std::vector<Light>{
            Light(
                    glm::vec3(1.5f, 1.5f, 1.5f),
                    glm::vec3(0.0f, 0.0f, 1.0f),
                    4.0f,
                    0.2f,
                    40.0f
            ),
            Light(
                    glm::vec3(-1.5f, 1.5f, -1.5f),
                    glm::vec3(1.0f, 0.0f, 0.0f),
                    2.0f,
                    0.2f,
                    20.0f
            ),
    })
{}


