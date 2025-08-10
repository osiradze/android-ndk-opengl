//
// Created by OSiradze on 13.07.25.
//

#include "objects/base/GameObject.h"
#include "camera/Camera.h"
#include "light/Light.h"
#include "environment/Environment.h"
#include "objects/primitives//Cube.h"
#include "objects/primitives/Plane.h"
#include <array>

class GameRenderer {
public:

    void onSurfaceCreated();

    void onDrawFrame();

    void onSurfaceChanged(int width, int height);

    void onDrag(float x, float y);

    void onDestroy();

private:
    Plane floor = Plane();
    Cube cube1 = Cube();
    Cube cube2 = Cube();

    std::unique_ptr<GLObjectData> lantern;

    Cube lightCube1 = Cube();
    Cube lightCube2 = Cube();

    glm::mat4 lightScaleModel = glm::mat4(1.0f);

    Environment env = Environment();
    std::vector<std::unique_ptr<GameObject>> gameObjects;

    void initObject();
    void updateObjects();

    static void initGLConfig();
    static void clearBuffers();

};