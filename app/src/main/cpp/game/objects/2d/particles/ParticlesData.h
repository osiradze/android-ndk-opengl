//
// Created by OSiradze on 30.08.25.
//

#pragma once

#include <__memory/unique_ptr.h>
#include "../../3d/data/GLObjectData.h"

class ParticlesData {
public:
    explicit ParticlesData(GLObjectData* objectDataPtr);

    unsigned int indicesCount = 100;
    unsigned int floatPerVertex = 7; // x, y, z, vx, vy, vz, size
    unsigned int stride = floatPerVertex * sizeof(float);
    unsigned int dataSize = indicesCount * floatPerVertex * sizeof(float);
    std::unique_ptr<float[]> data = std::make_unique<float[]>(indicesCount * floatPerVertex);
};