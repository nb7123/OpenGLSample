package com.mike.sample.util

import android.util.Log
import com.mike.sample.algorithm.MD5
import javax.crypto.Cipher
import javax.crypto.spec.IvParameterSpec
import javax.crypto.spec.SecretKeySpec


/**
 * Created by michael on 17-11-29.
 * 加密
 */
object Encrypt {
    private val HEX = "0123456789ABCDEF"
    private val CBC_PKCS5_PADDING = "AES/CBC/PKCS5Padding"  //AES是加密方式 CBC是工作模式 PKCS5Padding是填充模式
    private val AES = "AES"                                 //AES 加密
    private val SHA1PRNG = "SHA1PRNG"                       // SHA1PRNG 强随机种子算法, 要区别4.2以上版本的调用方法
    /*
     * 加密
     */
//    fun encrypt(key: String, cleartext: ByteArray): String? {
//        try {
//            val result = encrypt(key, cleartext)
//            var hexStr = ""
//            for (b in result) {
//                hexStr += "${b.toInt() and 0xFF} "
//            }
//
//            Log.d("Encrypt", "AES hex string:$hexStr")
//
//            return MD5.encryptMD5(result)
//        } catch (e: Exception) {
//            e.printStackTrace()
//        }
//
//        return null
//    }

    /*
    * 加密
    */
    fun encrypt(key: String, clear: ByteArray): ByteArray {
        // 给出字符串的密码
        val password = "password"

        // 密钥的比特位数，注意这里是比特位数
        // AES 支持 128、192 和 256 比特长度的密钥
        val keyLength = 128
        // 盐值的字节数组长度，注意这里是字节数组的长度
        // 其长度值需要和最终输出的密钥字节数组长度一致
        // 由于这里密钥的长度是 256 比特，则最终密钥将以 256/8 = 32 位长度的字节数组存在
        // 所以盐值的字节数组长度也应该是 32
//        val saltLength = keyLength/8

        // 先获取一个随机的盐值
        // 你需要将此次生成的盐值保存到磁盘上下次再从字符串换算密钥时传入
        // 如果盐值不一致将导致换算的密钥值不同
        // 保存密钥的逻辑官方并没写，需要自行实现
//        val random = SecureRandom()
//        val salt = ByteArray(saltLength)
//        random.nextBytes(salt)
//
//        // 将密码明文、盐值等使用新的方法换算密钥
//        val iterationCount = 1000
//        val keySpec = PBEKeySpec(key.toCharArray(), salt, iterationCount, keyLength)
//        val keyFactory = SecretKeyFactory.getInstance(AES)
//        // 到这里你就能拿到一个安全的密钥了
//        val keyBytes = keyFactory.generateSecret(keySpec).encoded

        val skeySpec = SecretKeySpec(key.toByteArray(), AES)
        val cipher = Cipher.getInstance(CBC_PKCS5_PADDING)
        cipher.init(Cipher.ENCRYPT_MODE, skeySpec, IvParameterSpec(ByteArray(cipher.blockSize)))
        val ecryptedBytes: ByteArray = cipher.doFinal(clear)

        Log.d("Clear", "Clear data: ${String(clear)}")

        Log.d("Encrypt", "Encrypted data: ${Common.bytes2HexString(ecryptedBytes)}, length[${ecryptedBytes.size}]")

        val decrypt = Cipher.getInstance(CBC_PKCS5_PADDING)
        decrypt.init(Cipher.DECRYPT_MODE, skeySpec, IvParameterSpec(ByteArray(cipher.blockSize)))
        Log.d("Decrypt", "Decrypted: ${String(decrypt.doFinal(ecryptedBytes))}")

        return MD5.encryptMD5(ecryptedBytes)
    }
}