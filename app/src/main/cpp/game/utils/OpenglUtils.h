//
// Created by OSiradze on 13.07.25.
//

#pragma once
#include <string>

class OpenglUtils {
public:
    static std::string loadShaderFromFile(const char* filePath);
    static bool createShader(int type, const char *code, unsigned int &shader);
    static bool createProgram(unsigned int vertexShader, unsigned int fragmentShader, unsigned int &program);
    static bool createProgram(unsigned int &program, const char *vertexPath, const char *fragmentPath);
    static unsigned char* loadImageFromAssets(const char* assetPath, int& width, int& height, int& channels);
};