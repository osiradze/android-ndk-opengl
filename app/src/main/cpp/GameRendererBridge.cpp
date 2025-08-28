//
// Created by OSiradze on 13.07.25.
//

#include <jni.h>
#include "game/GameRenderer.h"

std::unique_ptr<GameRenderer> gameRenderer;

extern "C"
JNIEXPORT void JNICALL
Java_com_siradze_workingwithc_GameRenderer_onSurfaceCreatedBridge(JNIEnv *env, jobject thiz) {
    gameRenderer = std::make_unique<GameRenderer>();
    gameRenderer->onSurfaceCreated();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_siradze_workingwithc_GameRenderer_onDrawFrameBridge(JNIEnv *env, jobject thiz) {
    gameRenderer->onDrawFrame();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_siradze_workingwithc_GameRenderer_onSurfaceChangedBridge(JNIEnv *env, jobject thiz, jint width, jint height) {
    gameRenderer->onSurfaceChanged(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_siradze_workingwithc_GameRenderer_onDragBridge(JNIEnv *env, jobject thiz, jfloat x,jfloat y) {
    gameRenderer->onDrag(x, y);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_siradze_workingwithc_GameRenderer_onDestroyBridge(JNIEnv *env, jobject thiz) {
    gameRenderer->onDestroy();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_siradze_workingwithc_GameRenderer_onTouchDownBridge(JNIEnv *env, jobject thiz, jint x,
                                                             jint y) {
    gameRenderer->onTouchDown(x, y);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_siradze_workingwithc_GameRenderer_onTouchBridge(JNIEnv *env, jobject thiz, jint x,
                                                         jint y) {
    gameRenderer->onTouch(x, y);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_siradze_workingwithc_GameRenderer_onTouchUpBridge(JNIEnv *env, jobject thiz, jint x,
                                                           jint y) {
    gameRenderer->onTouchUp(x, y);
}