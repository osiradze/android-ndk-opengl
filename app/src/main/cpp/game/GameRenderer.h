//
// Created by OSiradze on 13.07.25.
//

#include "objects/base/GameObject.h"
#include "camera/Camera.h"
#include "light/Light.h"
#include "environment/Environment.h"
#include "objects/box/Cube.h"
#include <array>

class GameRenderer {
    public:

        Cube cube = Cube();
        Environment env = Environment();
        std::array<GameObject*, 1> gameObjects {};

        void onSurfaceCreated();

        void onDrawFrame();

        void onSurfaceChanged(int width, int height);

        void onDrag(float x, float y);

        void onDestroy();
};