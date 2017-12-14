package com.mike.gvr.sample.util

import android.app.Activity
import android.content.Context
import android.content.res.AssetManager
import android.opengl.GLSurfaceView
import android.os.Build
import android.os.VibrationEffect
import android.os.Vibrator
import android.util.Log
import android.view.MotionEvent
import com.google.vr.ndk.base.AndroidCompat

import com.google.vr.ndk.base.GvrLayout

import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * Created by michael on 17-11-30.
 * Gl surface view helper class
 */

class GvrHelper(private val ctx: Activity) {
    private val surfaceView: GLSurfaceView = GLSurfaceView(ctx)
    val vrLayout: GvrLayout = GvrLayout(ctx)
    private var nativeRender: Long = 0

    // Note that pause and resume signals to the native renderer are performed on the GL thread,
    // ensuring thread-safety.
    private val pauseNativeRunnable = Runnable { nativePause(nativeRender) }

    private val resumeNativeRunnable = Runnable { nativeResume(nativeRender) }

    init {
        surfaceView.debugFlags = GLSurfaceView.DEBUG_CHECK_GL_ERROR or GLSurfaceView.DEBUG_LOG_GL_CALLS
        surfaceView.setEGLContextClientVersion(2)
        surfaceView.setEGLConfigChooser(8, 8, 8, 0, 0, 0)
        surfaceView.preserveEGLContextOnPause = true

        nativeRender = nativeCreateRender(javaClass.classLoader,
                ctx, vrLayout.gvrApi.nativeGvrContext)
        Log.d(LOG_TAG, "Native gvr context[${vrLayout.gvrApi.nativeGvrContext}], native render[$nativeRender]")
        nativeInitAssetManager(ctx.assets)
        surfaceView.setRenderer(object : GLSurfaceView.Renderer {
            override fun onSurfaceCreated(gl10: GL10, eglConfig: EGLConfig) {
                Log.i(LOG_TAG, "GL render, on surface created, ")
                nativeInitGL(nativeRender)
            }

            override fun onSurfaceChanged(gl10: GL10, width: Int, height: Int) {
                Log.i(LOG_TAG, "GL render, on surface changed, width[$width], height[$height]")
            }

            override fun onDrawFrame(gl10: GL10) {
                nativeDrawFrame(nativeRender)
            }
        })

        surfaceView.setOnTouchListener { _, motionEvent ->
            if (motionEvent.action == MotionEvent.ACTION_DOWN) {
                val virbrator = surfaceView.context.getSystemService(Context.VIBRATOR_SERVICE) as Vibrator
                if (Build.VERSION.SDK_INT < Build.VERSION_CODES.O) {
                    virbrator.vibrate(50)
                } else {
                    virbrator.vibrate(VibrationEffect.createOneShot(50, 100))
                }

                queueEvent(Runnable {
                    Log.i(LOG_TAG, "Queue event")
                    nativeOnTriggerEvent(nativeRender)
                })

                true
            } else {
                false
            }
        }

        vrLayout.setPresentationView(surfaceView)
    }

    fun queueEvent(event: Runnable) {
        surfaceView.queueEvent(event)
    }

    fun onPause() {
        queueEvent(pauseNativeRunnable)
        surfaceView.onPause()
        vrLayout.onPause()
    }

    fun onResume() {
        vrLayout.onResume()
        surfaceView.onResume()
        queueEvent(resumeNativeRunnable)
    }

    fun onDestroy() {
        vrLayout.shutdown()
        nativeDestroy(nativeRender)
        nativeRender = 0
    }

    fun onBackPressed() {
        vrLayout.onBackPressed()
    }

    private external fun nativeDrawFrame(nativeRender: Long)
    private external fun nativeInitGL(nativeRender: Long)
    private external fun nativeOnTriggerEvent(nativeRender: Long)
    private external fun nativeCreateRender(appClassLoader: ClassLoader, ctx: Context, nativeGvrContext: Long): Long

    private external fun nativePause(nativeRender: Long)
    private external fun nativeResume(nativeRender: Long)
    private external fun nativeDestroy(nativeRender: Long)
    private external fun nativeInitAssetManager(assetManager: AssetManager)


    companion object {
        init {
            System.loadLibrary("gvr")
            System.loadLibrary("gvr_audio")
            System.loadLibrary("native-lib")
        }

        private val LOG_TAG = GvrHelper::class.java.simpleName

        fun enableVRMode(activity: Activity) {
            // Enable VR Mode.
            AndroidCompat.setVrModeEnabled(activity, true)
        }

        // Enable async reprojection.
        fun enableAsyncReprojection(activity: Activity, vrLayout: GvrLayout) {
            if (vrLayout.setAsyncReprojectionEnabled(true)) {
                // Async reprojection decouples the app framerate from the display framerate,
                // allowing immersive interaction even at the throttled clockrates set by
                // sustained performance mode.
                AndroidCompat.setSustainedPerformanceMode(activity, true)
            }
        }
    }
}
