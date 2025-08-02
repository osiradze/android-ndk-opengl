//
// Created by OSiradze on 30.07.25.
//

#pragma once
#include "../game/objects/base/GameObjectData.h"

class ObjectLoader {
public:
    static std::unique_ptr<GLObjectData> loadObject(
            const std::string& objectPath
    );
};