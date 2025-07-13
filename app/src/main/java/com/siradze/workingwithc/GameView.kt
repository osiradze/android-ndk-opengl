package com.siradze.workingwithc

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet

class GameView(context: Context, attrs: AttributeSet) : GLSurfaceView(context) {

    private val gameRenderer: GameRenderer = GameRenderer()

    init {
        setEGLContextClientVersion(3)
        setRenderer(gameRenderer) // Set the renderer for this view
        renderMode = RENDERMODE_WHEN_DIRTY // Render continuously
    }

    override fun onDetachedFromWindow() {
        super.onDetachedFromWindow()

    }
}