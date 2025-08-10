//
// Created by OSiradze on 02.08.25.
//
#pragma once

#include "../base/GameObjectData.h"

class Plane {
private:
    int floatsPerVertex = 11;
    int dataCount = 44;
    float* vertexData = new float[dataCount] {
            -0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,   1.0f, 1.0f, 1.0f, // bottom-left
            0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f, 1.0f, // bottom-right
            0.5f, 0.0f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f, // top-right
            -0.5f, 0.0f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, 1.0f  // top-left
    };

    int indicesDataCount = 6;
    unsigned int* indices = new unsigned int[indicesDataCount] {
            0, 1, 2,
            2, 3, 0
    };

public:
    std::unique_ptr<GLObjectData> getData() {
        return std::make_unique<GLObjectData>(
                Plane::floatsPerVertex,  // floats per vertex
                Plane::dataCount,
                std::unique_ptr<float[]>(vertexData),
                Plane::indicesDataCount,
                std::unique_ptr<unsigned int[]>(indices)
        );
    }

};
