//
// Created by OSiradze on 27.07.25.
//

#pragma once

#include "../camera/Camera.h"
#include "../light/Light.h"

class Environment {
public:
    Camera camera;
    Light light;

    Environment();
};