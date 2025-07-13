//
// Created by OSiradze on 13.07.25.
//

#include "objects/GameObject.h"
#include "objects/triangle/Triangle.cpp"

class GameRenderer {
    public:
        GameObject* triangle = new Triangle();

        const void onSurfaceCreated();

        const void onDrawFrame();

        const void onSurfaceChanged(int width, int height);

        const void onDestroy();
};