//
// Created by OSiradze on 13.07.25.
//

#include "objects/GameObject.h"
#include "objects/triangle/Box.cpp"
#include <array>

class GameRenderer {
    public:
        std::array<GameObject*, 2> gameObjects;

        void onSurfaceCreated();

        void onDrawFrame();

        void onSurfaceChanged(int width, int height);

        void onDestroy();
};