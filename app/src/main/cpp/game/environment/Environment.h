//
// Created by OSiradze on 27.07.25.
//

#pragma once

#include "../camera/Camera.h"
#include "../light/Light.h"
#include <vector>

class Environment {
public:
    Camera camera;
    std::vector<Light> lights;
    bool colorIdMode = false;

    Environment();
};