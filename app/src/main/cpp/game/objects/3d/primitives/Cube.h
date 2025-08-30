//
// Created by OSiradze on 28.07.25.
//

#pragma once


#include "../data/GLObjectData.h"

class Cube {
private:
    int dataCount = 264;
    float* vertexData = new float[dataCount] {
            // Front face (z = 0.5) - Normal: (0, 0, 1)
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 1.0f,  // 0: bottom-left
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 1.0f,  // 1: bottom-right
            0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // 2: top-right
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,  0.0f, 0.0f, 0.0f,  // 3: top-left

            // Back face (z = -0.5) - Normal: (0, 0, -1)
            0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // 4: bottom-left
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // 5: bottom-right
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f,  // 6: top-right
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  // 7: top-left

            // Left face (x = -0.5) - Normal: (-1, 0, 0)
            -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // 8: bottom-left
            -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 1.0f,  // 9: bottom-right
            -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f,  // 10: top-right
            -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f,  // 11: top-left

            // Right face (x = 0.5) - Normal: (1, 0, 0)
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 1.0f, 1.0f,  // 12: bottom-left
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // 13: bottom-right
            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  // 14: top-right
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  // 15: top-left

            // Bottom face (y = -0.5) - Normal: (0, -1, 0)
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // 16: bottom-left
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  // 17: bottom-right
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  // 18: top-right
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,  // 19: top-left

            // Top face (y = 0.5) - Normal: (0, 1, 0)
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 0.0f,  // 20: bottom-left
            0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  // 21: bottom-right
            0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  // 22: top-right
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f, 0.0f   // 23: top-left
    };

    int indicesDataCount = 36;
    unsigned int* indices = new unsigned int[indicesDataCount] {
            // Front face (+Z) - CCW from outside
            0, 1, 2,   0, 2, 3,

            // Back face (-Z) - CCW from outside
            4, 5, 6,   4, 6, 7,

            // Left face (-X) - CCW from outside
            8, 9, 10,  8, 10, 11,

            // Right face (+X) - CCW from outside
            12, 13, 14, 12, 14, 15,

            // Bottom face (-Y) - CCW from outside
            16, 17, 18, 16, 18, 19,

            // Top face (+Y) - CCW from outside
            20, 21, 22, 20, 22, 23
    };
public:
    std::unique_ptr<GLObjectData> getData() {
        return std::make_unique<GLObjectData>(
                "Cube",
                11,  // floats per vertex
                dataCount,
                std::unique_ptr<float[]>(vertexData),
                indicesDataCount,
                std::unique_ptr<unsigned int[]>(indices)
        );
    }
};