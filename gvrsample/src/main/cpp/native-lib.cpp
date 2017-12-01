#include <jni.h>
#include <string>
#include "util/Log.h"
#include "engine/Engine.h"

#define JNI_METHOD(return_type, method_name)    \
    JNIEXPORT return_type JNICALL               \
    Java_com_mike_gvr_sample_util_GvrHelper_##method_name

namespace {
    inline jlong jptr(Engine *nativeEngine) {
        return reinterpret_cast<intptr_t>(nativeEngine);
    }

    inline Engine *native(jlong ptr) {
        return reinterpret_cast<Engine *>(ptr);
    }
}


/**
 * native draw frame
 */
extern "C" {
JNIEXPORT jstring

JNICALL
Java_com_mike_opengl_sample_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

/**
 * draw frame
 */
JNI_METHOD(void, nativeDrawFrame)
(JNIEnv *env,
 jobject instance,
 jlong nativeRender) {

    native(nativeRender)->draw();

}

/**
 * initialize gl state machine
 */
JNI_METHOD(void, nativeInitGL)
(JNIEnv *env,
 jobject instance,
 jlong nativeRender) {

    Log::i("native-lib", "Native initialize gl");
    native(nativeRender)->init();

}

/**
 * trigger event
 */
JNI_METHOD(void, nativeOnTriggerEvent)
(JNIEnv *env,
 jobject instance,
 jlong nativeRender) {

    Log::i("native-lib", "Native on trigger event");

}

/**
 * create render
 */
JNI_METHOD(jlong, nativeCreateRender)
(JNIEnv *env,
 jobject instance,
 jobject appClassLoader,
 jobject ctx,
 jlong nativeGvrContext) {
    Log::i("native-lib", "Native create render");

    return jptr(new Engine(nativeGvrContext));
}

/**
 * pause render
 * @param env
 * @param instance
 * @param nativeGvrContext
 */
JNI_METHOD(void, nativePause)
(JNIEnv *env,
 jobject instance,
 jlong nativeRender) {
    Log::i("native-lib", "Native pause render");
}

/**
 * resume render
 * @param env
 * @param instance
 * @param nativeGvrContext
 */
JNI_METHOD(void, nativeResume)
(JNIEnv *env,
 jobject instance,
 jlong nativeRender) {
    Log::i("native-lib", "Native resume render");
}

/**
 * destroy render
 * @param env
 * @param instance
 * @param nativeGvrContext
 */
JNI_METHOD(void, nativeDestroy)
(JNIEnv *env,
 jobject instance,
 jlong nativeRender) {
    Log::i("native-lib", "Native destroy render");

    delete(native(nativeRender));
}
}