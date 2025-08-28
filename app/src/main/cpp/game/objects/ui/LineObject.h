//
// Created by OSiradze on 28.08.25.
//

#pragma once

#include "../base/GameObject.h"
#include "../base/ShadersPaths.h"
#include "../../uievents/TouchDown.h"
#include <array>

struct LineObjectData {
    unsigned int indicesCount = 100;
    unsigned int floatPerVertex = 2; // x, y
    unsigned int stride = floatPerVertex * sizeof(float);
    unsigned int vertexDataSize = indicesCount * floatPerVertex * sizeof(float);
    std::unique_ptr<float[]> vertexData = std::make_unique<float[]>(indicesCount * floatPerVertex);
};

class LineObject : public GameObject {

public:
    explicit LineObject(TouchDown* touchPosition) : touchPosition(touchPosition) {}

    void init() override;
    void onDraw() override;
    void destroy() override;
private:
    unsigned int vao = 0;
    unsigned int vbo = 0;

    std::unique_ptr<LineObjectData> data = std::make_unique<LineObjectData>();

    unsigned int shaderProgram = 0;
    unsigned int computeProgram = 0;

    int u_index = 0;
    int u_touch = 0;
    int u_mode = 0; // 1 - start, 2 - active, 3 - end
    int u_vertex_number = 0;


    unsigned int index = 0;

    TouchDown* touchPosition;

    ShadersPaths shaders = {
            .vertexShader = "shaders/line/line_v.vert",
            .fragmentShader = "shaders/line/line_f.frag",
            .computeShader = "shaders/line/line_c.comp"
    };

    void initData();

};
