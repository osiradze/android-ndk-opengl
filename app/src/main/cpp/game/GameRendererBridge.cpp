//
// Created by OSiradze on 13.07.25.
//

#include <jni.h>
#include "GameRenderer.h"

GameRenderer gameRenderer = GameRenderer();

extern "C"
JNIEXPORT void JNICALL
Java_com_siradze_workingwithc_GameRenderer_onSurfaceCreatedBridge(JNIEnv *env, jobject thiz) {
    gameRenderer.onSurfaceCreated();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_siradze_workingwithc_GameRenderer_onDrawFrameBridge(JNIEnv *env, jobject thiz) {
    gameRenderer.onDrawFrame();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_siradze_workingwithc_GameRenderer_onSurfaceChangedBridge(JNIEnv *env, jobject thiz, jint width, jint height) {
    gameRenderer.onSurfaceChanged(width, height);
}