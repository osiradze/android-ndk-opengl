//
// Created by OSiradze on 30.07.25.
//

#pragma once
#include "../game/objects/3d/data/GLObjectData.h"

class ObjectLoader {
public:
    static std::unique_ptr<GLObjectData> loadObject(
            const std::string& objectPath
    );
};