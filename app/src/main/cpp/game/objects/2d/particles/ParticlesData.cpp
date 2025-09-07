//
// Created by OSiradze on 30.08.25.
//
#include "ParticlesData.h"

ParticlesData::ParticlesData(GLObjectData* objectDataPtr) {
    if (!data) return;
    int repeatCount = indicesCount / objectDataPtr->indicesCount;
    repeatCount--;
    //repeatCount = 1;
    for(int r = 0; r < repeatCount; r++) {
        float step = 1.0f - (1.0f / repeatCount) * r;
         // offset to center particles
        unsigned int chunkIndex = r * objectDataPtr->indicesCount * floatPerVertex;
        for (int i = 0; i < objectDataPtr->indicesCount; i++) {
            // position
            auto vertexPosition = i * objectDataPtr->numberOfFloatsPerVertex;

            float scatter = 0.5f;
            data[chunkIndex + i * floatPerVertex + 0] = objectDataPtr->vertexData[vertexPosition + 0] * step + MathUtils::randomFloat(-scatter, scatter) * (1.0 - step); // x
            data[chunkIndex + i * floatPerVertex + 1] = objectDataPtr->vertexData[vertexPosition + 1] * step + MathUtils::randomFloat(-scatter, scatter) * (1.0 - step); // x
            data[chunkIndex + i * floatPerVertex + 2] = objectDataPtr->vertexData[vertexPosition + 2] * step + MathUtils::randomFloat(-scatter, scatter) * (1.0 - step); // x
            // velocity
         /*   data[chunkIndex + i * floatPerVertex + 3] = MathUtils::randomFloat() * 2.0f - 1.0f; // vx
            data[chunkIndex + i * floatPerVertex + 4] = MathUtils::randomFloat(); // vy
            data[chunkIndex + i * floatPerVertex + 5] = MathUtils::randomFloat() * 2.0f - 1.0f; // vz*/
            // size
            data[chunkIndex + i * floatPerVertex + 6] = MathUtils::randomFloat() * 2.0f + 2.0f; // size*/
        }
    }
}

