package com.mike.sample

import android.os.Bundle
import android.support.design.widget.Snackbar
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import com.crashlytics.android.Crashlytics
import com.google.firebase.analytics.FirebaseAnalytics
import com.mike.sample.algorithm.MD5
import com.mike.sample.util.Common
import com.mike.sample.util.Encrypt

import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    companion object {
        private val LOG_TAG = MainActivity::class.java.simpleName
    }

    private var analytics: FirebaseAnalytics? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        setSupportActionBar(toolbar)

        analytics = FirebaseAnalytics.getInstance(this)

        fab.setOnClickListener { view ->
//            Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
//                    .setAction("Action", null).show()

//            testCrashReport()
            testFBLog()
//            encrypt()
        }
    }

    private fun testCrashReport() {
        Crashlytics.getInstance().crash()
    }

    private fun testFBLog() {
        val bundle = Bundle()
        bundle.putString("KEY1", "Value1")
        bundle.putString("KEY2", "Value2")
        analytics?.logEvent(FirebaseAnalytics.Event.SELECT_CONTENT, bundle)
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.menu_main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        return when (item.itemId) {
            R.id.action_settings -> true
            else -> super.onOptionsItemSelected(item)
        }
    }

    private fun encrypt() {
        val data = "321654987"
        val md5Data = MD5.encryptMD5(data.toByteArray())
        Log.i(LOG_TAG, Common.bytes2HexString(md5Data))

        Log.i(LOG_TAG, Common.bytes2HexString(Encrypt.encrypt("1234567890123456", md5Data)))
    }
}
