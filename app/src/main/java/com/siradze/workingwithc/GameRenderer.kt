package com.siradze.workingwithc

import android.opengl.GLES20.GL_COLOR_BUFFER_BIT
import android.opengl.GLES20.GL_DEPTH_BUFFER_BIT
import android.opengl.GLES20.GL_DEPTH_TEST
import android.opengl.GLES20.glClear
import android.opengl.GLES20.glClearColor
import android.opengl.GLES20.glEnable
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

    fun onDestroy() {
        onDestroyBridge()
    }

    external fun onDragBridge(x: Float, y: Float)

    private external fun onSurfaceCreatedBridge()

    private external fun onDrawFrameBridge()

    private external fun onSurfaceChangedBridge(width: Int, height: Int)

    private external fun onDestroyBridge()
}