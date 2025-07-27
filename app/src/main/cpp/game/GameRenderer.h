//
// Created by OSiradze on 13.07.25.
//

#include "objects/base/GameObject.h"
#include "camera/Camera.h"
#include "light/Light.h"
#include <array>

class GameRenderer {
    public:
        Camera camera = Camera::createDefaultCamera();
        Light light = Light(
                glm::vec3(5.0f, 0.5f, 5.0f),
                glm::vec3(0.7f, 0.5f, 1.0f),
                2.0f
        );
        std::array<GameObject*, 2> gameObjects {};

        void onSurfaceCreated();

        void onDrawFrame();

        void onSurfaceChanged(int width, int height);

        void onDrag(float x, float y);

        void onDestroy();
};