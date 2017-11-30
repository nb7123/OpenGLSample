//
// Created by michael on 17-11-28.
//

#ifndef OPENGLSAMPLE_ENGINE_H
#define OPENGLSAMPLE_ENGINE_H


#include <EGL/egl.h>

#include <android/sensor.h>
#include "../util/Log.h"

class Engine {
private:
    static const char *LOG_TAG;
    static void handle_cmd(struct android_app *app, int32_t cmd);

    static Engine *instance;

    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;

    ASensorManager *sensorMgr;
    const ASensor *accelerometerSensor;
    ASensorEventQueue *sensorEventQueue;

    Engine(struct android_app *app);

public:

    static Engine *getInstance(struct android_app *app) {
        if (nullptr == instance) {
            instance = new Engine(app);

            instance->sensorMgr = ASensorManager_getInstance();
            if (nullptr == instance->sensorMgr) {
                Log::e(LOG_TAG, "Get sensor manager instance failed!");
            } else {
                instance->accelerometerSensor = ASensorManager_getDefaultSensor(instance->sensorMgr,
                                                                                ASENSOR_TYPE_ACCELEROMETER);
                instance->sensorEventQueue =
                        ASensorManager_createEventQueue(instance->sensorMgr,// 传感器管理器
                                                        app->looper,// 主循环
                                                        LOOPER_ID_USER,//
                                                        nullptr, nullptr);
            }

        }

        return instance;
    }

    /**
     * 初始化引擎
     * @param app   android app
     */
    void init(struct android_app *app);

    /**
     * 绘制
     */
    void draw();

    /**
     * 处理加速传感器事件
     */
    void pullAccelerometerEvent();

    /**
     * 手动释放资源
     */
    void release();

    ~Engine();
};


#endif //OPENGLSAMPLE_ENGINE_H
