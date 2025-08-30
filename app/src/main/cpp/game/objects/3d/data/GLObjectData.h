//
// Created by OSiradze on 28.07.25.
//

#pragma once
#include <array>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "../../base/Translation.h"
#include "../../../utils/MathUtils.h"
#include <random>
#include <utility>

struct GLObjectData {

    unsigned int numberOfFloatsPerVertex;
    unsigned int stride;
    unsigned int vertexDataSize;
    unsigned int indicesSize;
    unsigned int indicesCount;
    std::unique_ptr<float[]> vertexData;
    std::unique_ptr<unsigned int[]> indices;
    std::string name;

    GLObjectData(
            std::string name,
            int numberOfFloatsPerVertex,
            int vertexDataCount,
            std::unique_ptr<float[]> vertexData = nullptr,
            int indicesCount = 0,
            std::unique_ptr<unsigned int[]> indices = nullptr
    ):
    numberOfFloatsPerVertex(numberOfFloatsPerVertex),
    stride(numberOfFloatsPerVertex * sizeof(float)),
    vertexDataSize(vertexDataCount * sizeof(float)),
    indicesSize(indicesCount * sizeof(unsigned int)),
    indicesCount(indicesCount),
    vertexData(std::move(vertexData)),
    indices(std::move(indices)),
    name(std::move(name)){}
private:
    Translation translation = Translation();

public:

    bool outline = false;
    glm::vec4 colorId = glm::vec4(MathUtils::randomFloat(), MathUtils::randomFloat(), MathUtils::randomFloat(), 1.0f); // default white color id

    Translation* getTranslation() {
        return &translation;
    }

    //clear memory after transferring data to GPU
    void freeVertexDataFromMemory() {
        vertexData.reset();
        indices.reset();
    }

};