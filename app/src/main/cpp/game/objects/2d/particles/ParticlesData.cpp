//
// Created by OSiradze on 30.08.25.
//
#include "ParticlesData.h"

ParticlesData::ParticlesData(GLObjectData* objectDataPtr) {
    if (!data) return;
    for (unsigned int i = 0; i < objectDataPtr->indicesCount; i++) {
        // position
        auto vertexPosition = i * objectDataPtr->numberOfFloatsPerVertex;
        data[i * floatPerVertex + 0] = objectDataPtr->vertexData[vertexPosition]; // x
        data[i * floatPerVertex + 1] = objectDataPtr->vertexData[vertexPosition + 1]; // y
        data[i * floatPerVertex + 2] = objectDataPtr->vertexData[vertexPosition + 2]; // z
        // velocity
        data[i * floatPerVertex + 3] = 0.0f; // vx
        data[i * floatPerVertex + 4] = 0.0f; // vy
        data[i * floatPerVertex + 5] = 0.0f; // vz
        // size
        data[i * floatPerVertex + 6] =  0.0f; // size
    }
}

