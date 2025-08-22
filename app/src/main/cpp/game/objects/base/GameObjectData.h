//
// Created by OSiradze on 28.07.25.
//

#pragma once
#include <array>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/glm.hpp"
#include "Translation.h"

struct GLObjectData {
    unsigned int stride;
    unsigned int vertexDataSize;
    unsigned int indicesSize;
    unsigned int indicesCount;
    std::unique_ptr<float[]> vertexData;
    std::unique_ptr<unsigned int[]> indices;

    GLObjectData(
            int numberOfFloatsPerVertex,
            int vertexDataCount,
            std::unique_ptr<float[]> vertexData = nullptr,
            int indicesCount = 0,
            std::unique_ptr<unsigned int[]> indices = nullptr
    ):
    stride(numberOfFloatsPerVertex * sizeof(float)),
    vertexDataSize(vertexDataCount * sizeof(float)),
    indicesSize(indicesCount * sizeof(unsigned int)),
    indicesCount(indicesCount),
    vertexData(std::move(vertexData)),
    indices(std::move(indices)) {}
private:
    Translation translation = Translation();

public:

    Translation* getTranslation() {
        return &translation;
    }

    //clear memory after transferring data to GPU
    void freeVertexDataFromMemory() {
        vertexData.reset();
        indices.reset();
    }

};