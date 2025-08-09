//
// Created by OSiradze on 09.08.25.
//

#pragma once

#include <map>
#include <cmath>

struct Attenuation {
    float constant, linear, quadratic;
    static Attenuation getNearestAttenuation(float distance);
};



