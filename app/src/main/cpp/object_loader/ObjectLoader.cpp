//
// Created by OSiradze on 30.07.25.
//

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <android/log.h>
#include "ObjectLoader.h"
#include "../assets/AssetManager.h"
#include "glm/ext/matrix_transform.hpp"

std::unique_ptr<GLObjectData> ObjectLoader::loadObject(
        const std::string& objectPath
){
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string objectContent = AssetManager::getFileStringContent(objectPath.c_str());
    std::istringstream iss(objectContent);
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, &iss);

    if (!ret) {
        __android_log_print(ANDROID_LOG_ERROR, "OBJ", "Failed to load: %s", err.c_str());
    }

    for(int i = 0; i < shapes.size(); i++) {
        const tinyobj::shape_t& shape = shapes[i];
        __android_log_print(ANDROID_LOG_INFO, "OBJ", "Shape %d: %s", i, shape.name.c_str());
    }

    int numberOfFloatsPerVertex = 11; // Position (3) + Normal (3) + TexCoord (2) + Color (3)

    float* vertexData = attrib.vertices.data();
    float* colorsData = attrib.colors.data();
    float* texcoordsData = attrib.texcoords.data();
    float* normalsData = attrib.normals.data();

    std::vector<float> vertexDataVector;


    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            // Position
            int vi = index.vertex_index * 3;
            vertexDataVector.push_back(vertexData[vi + 0]);
            vertexDataVector.push_back(vertexData[vi + 1]);
            vertexDataVector.push_back(vertexData[vi + 2]);

            // Normal
            if (!attrib.normals.empty() && index.normal_index >= 0) {
                int ni = index.normal_index * 3;
                vertexDataVector.push_back(normalsData[ni + 0]);
                vertexDataVector.push_back(normalsData[ni + 1]);
                vertexDataVector.push_back(normalsData[ni + 2]);
            } else {
                vertexDataVector.insert(vertexDataVector.end(), {0.0f, 0.0f, 0.0f});
            }

            // TexCoord
            if (!attrib.texcoords.empty() && index.texcoord_index >= 0) {
                int ti = index.texcoord_index * 2;
                vertexDataVector.push_back(texcoordsData[ti + 0]);
                vertexDataVector.push_back(texcoordsData[ti + 1]);
            } else {
                vertexDataVector.insert(vertexDataVector.end(), {0.0f, 0.0f});
            }

            // Color
            if (!attrib.colors.empty() && index.vertex_index >= 0) {
                int ci = index.vertex_index * 3;
                vertexDataVector.push_back(colorsData[ci + 0]);
                vertexDataVector.push_back(colorsData[ci + 1]);
                vertexDataVector.push_back(colorsData[ci + 2]);
            } else {
                vertexDataVector.insert(vertexDataVector.end(), {1.0f, 1.0f, 1.0f});
            }

        }
    }

    std::vector<unsigned int> indicesVector;
    for (uint32_t i = 0; i < vertexDataVector.size() / numberOfFloatsPerVertex; ++i) {
        indicesVector.push_back(i);
    }

    auto vertexCopy = std::make_unique<float[]>(vertexDataVector.size());
    std::copy(vertexDataVector.begin(), vertexDataVector.end(), vertexCopy.get());

    auto indexCopy = std::make_unique<unsigned int[]>(indicesVector.size());
    std::copy(indicesVector.begin(), indicesVector.end(), indexCopy.get());
    return std::make_unique<GLObjectData>(
            glm::mat4(1.0f),
            numberOfFloatsPerVertex,
            vertexDataVector.size(), // Vertex count
              std::move(vertexCopy), // Vertex data
              indicesVector.size(), // Indices count
              std::move(indexCopy)  // Indices data
      );
}

