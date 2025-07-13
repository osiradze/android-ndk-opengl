package com.siradze.workingwithc

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GameRenderer: GLSurfaceView.Renderer {

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        onSurfaceCreatedBridge()
    }

    override fun onDrawFrame(gl: GL10?) {
        onDrawFrameBridge()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        onSurfaceChangedBridge(width, height)
    }

    private external fun onSurfaceCreatedBridge()

    private external fun onDrawFrameBridge()

    private external fun onSurfaceChangedBridge(width: Int, height: Int)
}