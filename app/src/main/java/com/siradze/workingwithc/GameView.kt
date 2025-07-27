package com.siradze.workingwithc

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.view.MotionEvent

class GameView(context: Context, attrs: AttributeSet) : GLSurfaceView(context) {

    private val gameRenderer: GameRenderer = GameRenderer()

    init {
        setEGLContextClientVersion(3)
        setRenderer(gameRenderer) // Set the renderer for this view
        renderMode = RENDERMODE_CONTINUOUSLY // Render continuously
        initTouch()
    }

    override fun onDetachedFromWindow() {
        super.onDetachedFromWindow()
        gameRenderer.onDestroy()
    }

    fun initTouch() {

        var lastX = 0f
        var lastY = 0f

        setOnTouchListener { v, event ->
            when (event.action) {
                MotionEvent.ACTION_DOWN -> {
                    lastX = event.rawX
                    lastY = event.rawY
                    true
                }

                MotionEvent.ACTION_MOVE -> {
                    val currentX = event.rawX
                    val currentY = event.rawY

                    val deltaX = currentX - lastX
                    val deltaY = currentY - lastY

                    // 👇 Use deltaX and deltaY here
                    gameRenderer.onDragBridge(deltaX, deltaY)

                    lastX = currentX
                    lastY = currentY
                    true
                }

                MotionEvent.ACTION_UP -> {
                    v.performClick() // good practice
                    true
                }

                else -> false
            }
        }
    }

}