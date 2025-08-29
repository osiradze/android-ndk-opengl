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
#include "uievents/TouchDown.h"
#include "objects/ui/LineObject.h"
#include <array>

class GameRenderer {
public:

    void onSurfaceCreated();

    void onDrawFrame();

    void onSurfaceChanged(int width, int height);

    void onDrag(float x, float y);

    void onTouchDown(int x, int y);

    void onTouch(int x, int y);

    void onTouchUp(int x, int y);

    void onDestroy();

private:
    // for rendering to texture
    std::unique_ptr<Screen> screen;
    // for color id picking
    std::unique_ptr<Screen> colorIdScreen;

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


    std::unique_ptr<TouchDown> touch = std::make_unique<TouchDown>(TouchDown { });
    std::unique_ptr<TouchDownTmp> touchTmp = nullptr;

    std::unique_ptr<LineObject> line = std::make_unique<LineObject>(touch.get());


    void initObject();
    void updateObjects();
    void drawObjects();
    void handleColorIdPicking();
    void copyTouchTmp();

    static void initGLConfig();
    static void clearBuffers();

};