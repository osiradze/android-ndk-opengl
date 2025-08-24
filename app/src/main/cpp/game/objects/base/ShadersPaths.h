//
// Created by OSiradze on 29.07.25.
//

#pragma once

struct ShadersPaths {
    std::string vertexShader;
    std::string fragmentShader;
    std::string stencilFragmentShader = "shaders/stencil_f.frag";
    std::string colorIdFragmentShader = "shaders/color_id_f.frag";
};