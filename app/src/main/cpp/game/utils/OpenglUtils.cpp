//
// Created by OSiradze on 13.07.25.
//


#include <cstdio>
#include "OpenglUtils.h"
#include "../../asset/AssetManager.h"
#include <GLES3/gl3.h>
#include <android/log.h>

#include <fstream>
#include <sstream>
#include <string>


bool OpenglUtils::createShader(int type, const char *code, unsigned int &shader) {
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        __android_log_print(ANDROID_LOG_ERROR, "GameTag", "%s", infoLog);
        return false;
    }
    return true;
}

bool OpenglUtils::createProgram(unsigned int vertexShader, unsigned int fragmentShader, unsigned int &program) {
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        printf("ERROR::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
        return false;
    }
    return true;
}

std::string OpenglUtils::loadShaderFromFile(const char *filePath) {
    auto assetManager = AssetManager::assetManager;
    if (!assetManager) {
        __android_log_print(ANDROID_LOG_ERROR, "ShaderLoader", "AssetManager is null!");
        return "";
    }

    AAsset* file = AAssetManager_open(assetManager, filePath, AASSET_MODE_BUFFER);
    if (!file) {
        __android_log_print(ANDROID_LOG_ERROR, "ShaderLoader", "Failed to open: %s", filePath);
        return "";
    }

    size_t size = AAsset_getLength(file);
    std::string content(size, '\0');
    AAsset_read(file, content.data(), size);
    AAsset_close(file);
    return content;
}