//
// Created by OSiradze on 13.07.25.
//

#include "objects/base/GameObject.h"
#include "camera/Camera.h"
#include "light/Light.h"
#include "environment/Environment.h"
#include "objects/primitives//Cube.h"
#include "objects/primitives/Plane.h"
#include "screen/Screen.h"
#include <array>

class GameRenderer {
public:

    void onSurfaceCreated();

    void onDrawFrame();

    void onSurfaceChanged(int width, int height);

    void onDrag(float x, float y);

    void onDestroy();

private:
    std::unique_ptr<Screen> screen;

    std::unique_ptr<GLObjectData> floor = Plane().getData();
    std::unique_ptr<GLObjectData> cube1 = Cube().getData();
    std::unique_ptr<GLObjectData> cube2 = Cube().getData();

    std::unique_ptr<GLObjectData> lightCube1 = Cube().getData();
    std::unique_ptr<GLObjectData> lightCube2 = Cube().getData();

    std::unique_ptr<GLObjectData> lantern;

    Environment env = Environment();
    std::vector<std::unique_ptr<GameObject>> gameObjects;

    std::vector<GLObjectData*> allData {
            floor.get(), cube1.get(), cube2.get(), lightCube1.get(), lightCube2.get()
    };

    void initObject();
    void updateObjects();

    static void initGLConfig();
    static void clearBuffers();

};