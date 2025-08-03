//
// Created by OSiradze on 28.07.25.
//

#pragma once
#include <array>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/glm.hpp"
#include "Translation.h"

struct GLObjectData {
    unsigned int numberOfFloatsPerVertex;
    std::unique_ptr<float[]> vertexData;
    std::unique_ptr<unsigned int[]> indices;

    GLObjectData(
            int numberOfFloatsPerVertex,
            int vertexDataCount,
            std::unique_ptr<float[]> vertexData = nullptr,
            int indicesCount = 0,
            std::unique_ptr<unsigned int[]> indices = nullptr
    ):
    numberOfFloatsPerVertex(numberOfFloatsPerVertex),
    vertexDataSize(vertexDataCount * sizeof(float)),
    vertexData(std::move(vertexData)),
    indicesCount(indicesCount),
    indicesSize(indicesCount * sizeof(unsigned int)),
    indices(std::move(indices)) {}
private:
    Translation translation = Translation();

public:
    unsigned int stride = numberOfFloatsPerVertex * sizeof(float);
    unsigned int vertexDataSize;
    unsigned int indicesSize;
    unsigned int indicesCount;

    Translation* getTranslation() {
        return &translation;
    }

};