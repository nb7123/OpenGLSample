package com.mike.gvr.sample

import android.app.Activity
import android.os.Bundle
import android.view.View
import com.mike.gvr.sample.util.GvrHelper

class MainActivity : Activity() {
    companion object {
        private val LOG_TAG = MainActivity::class.java.simpleName
    }

    private var vrHelper: GvrHelper? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setImmersiveSticky()
        setupWindowProps()

        vrHelper = GvrHelper(this)

        setContentView(vrHelper?.vrLayout)

        GvrHelper.enableAsyncReprojection(this, vrHelper?.vrLayout!!)
        GvrHelper.enableVRMode(this)
    }

    override fun onPause() {
        super.onPause()

        vrHelper?.onPause()
    }

    override fun onResume() {
        super.onResume()

        vrHelper?.onResume()
    }

    override fun onDestroy() {
        super.onDestroy()

        vrHelper?.onDestroy()
    }

    override fun onBackPressed() {
        super.onBackPressed()
        vrHelper?.onBackPressed()
    }

    private fun setupWindowProps() {
        window.decorView
                .setOnSystemUiVisibilityChangeListener { visibility ->
                    if ((visibility and View.SYSTEM_UI_FLAG_FULLSCREEN) == 0) {
                        setImmersiveSticky()
                    }
                }
    }

    private fun setImmersiveSticky() {
        window.decorView.systemUiVisibility= (View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                or View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                or View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                or View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                or View.SYSTEM_UI_FLAG_FULLSCREEN
                or View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY)
    }
}
