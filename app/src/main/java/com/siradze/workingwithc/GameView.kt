package com.siradze.workingwithc

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet

class GameView(context: Context, attrs: AttributeSet) : GLSurfaceView(context) {

    init {
        setEGLContextClientVersion(3)
        setRenderer(GameRenderer()) // Set the renderer for this view
        renderMode = RENDERMODE_CONTINUOUSLY // Render continuously
    }
}