//
// Created by OSiradze on 13.07.25.
//

#include "objects/GameObject.h"
#include "camera/Camera.h"
#include <array>

class GameRenderer {
    public:
        Camera camera = Camera::createDefaultCamera();
        std::array<GameObject*, 2> gameObjects;

        void onSurfaceCreated();

        void onDrawFrame();

        void onSurfaceChanged(int width, int height);

        void onDestroy();
};