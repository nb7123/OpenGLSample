//
// Created by michael on 17-11-28.
//

#ifndef OPENGLSAMPLE_COMMON_UTIL_H
#define OPENGLSAMPLE_COMMON_UTIL_H

#include <android/log.h>


class Log {

public:
    /**
     * 打印信息
     * @param tag   tag
     * @param msg   消息
     * @param ...   消息参数
     */
    static inline void i(const char *tag, const char *msg, ...) {
        va_list ap;
        va_start(ap, msg);

        __android_log_vprint(ANDROID_LOG_INFO, tag, msg, ap);
    }
    /**
     * 打印调试信息
     * @param tag   tag
     * @param msg   消息
     * @param ...   消息参数
     */
    static inline void d(const char *tag, const char *msg, ...) {
        va_list ap;
        va_start(ap, msg);

        __android_log_vprint(ANDROID_LOG_DEBUG, tag, msg, ap);
    }
    /**
     * 打印错误信息
     * @param tag   tag
     * @param msg   消息
     * @param ...   消息参数
     */
    static inline void e(const char *tag, const char *msg, ...) {
        va_list ap;
        va_start(ap, msg);

        __android_log_vprint(ANDROID_LOG_ERROR, tag, msg, ap);
    }

    /**
     * 打印详细信息
     * @param tag   tag
     * @param msg   消息
     * @param ...   消息参数
     */
    static void w(const char *tag, const char *msg, ...) {
        va_list ap;
        va_start(ap, msg);

        __android_log_vprint(ANDROID_LOG_WARN, tag, msg, ap);
    }

    /**
     * 打印详细信息
     * @param tag   tag
     * @param msg   消息
     * @param ...   消息参数
     */
    static void v(const char *tag, const char *msg, ...) {
        va_list ap;
        va_start(ap, msg);

        __android_log_vprint(ANDROID_LOG_VERBOSE, tag, msg, ap);
    }
};


#endif //OPENGLSAMPLE_COMMON_UTIL_H
