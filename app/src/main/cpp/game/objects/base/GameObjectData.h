//
// Created by OSiradze on 28.07.25.
//

#pragma once
#include <array>
#include "glm/ext/matrix_float4x4.hpp"


struct GLObjectData {
    glm::mat4 model;
    unsigned int numberOfFloatsPerVertex;
    std::unique_ptr<float[]> vertexData;
    std::unique_ptr<unsigned int[]> indices;

    GLObjectData(
            glm::mat4 model,
            int numberOfFloatsPerVertex,
            int vertexDataCount,
            std::unique_ptr<float[]> vertexData = nullptr,
            int indicesCount = 0,
            std::unique_ptr<unsigned int[]> indices = nullptr
    ):
    model(model),
    numberOfFloatsPerVertex(numberOfFloatsPerVertex),
    vertexDataSize(vertexDataCount * sizeof(float)),
    vertexData(std::move(vertexData)),
    indicesCount(indicesCount),
    indicesSize(indicesCount * sizeof(unsigned int)),
    indices(std::move(indices)) {}

public:
    unsigned int stride = numberOfFloatsPerVertex * sizeof(float);
    unsigned int vertexDataSize;
    unsigned int indicesSize;
    unsigned int indicesCount;
};