package com.mike.sample.algorithm

import java.security.MessageDigest


/**
 * Created by michael on 17-11-29.
 * MD5 加密
 */
object MD5 {
    @Throws(Exception::class)
    fun encryptMD5(data: ByteArray): ByteArray {

        val md5 = MessageDigest.getInstance("MD5")
        md5.update(data)

        return md5.digest()
    }
}