package com.mike.sample.util

/**
 * Created by michael on 17-11-29.
 */
object Common {
    fun bytes2HexString(bytes: ByteArray): String {
        var result = ""
        for (b in bytes) {
            result += "${Integer.toHexString(b.toInt() and 0xFF)}"
        }

        return result
    }
}