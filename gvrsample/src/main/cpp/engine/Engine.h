//
// Created by michael on 17-11-28.
//

#ifndef OPENGLSAMPLE_ENGINE_H
#define OPENGLSAMPLE_ENGINE_H


#include <EGL/egl.h>

#include <android/sensor.h>
#include <vr/gvr/capi/include/gvr.h>
#include <vr/gvr/capi/include/gvr_types.h>

#include "../util/Log.h"
#include "../objects/shape/triangle/Triangle.h"
#include "../objects/shape/square/Square.h"

static const uint64_t kPredictionTimeWithoutVsyncNanos = 50000000;

class Engine {
private:
    static const char *LOG_TAG;

    ASensorManager *sensorMgr;
    const ASensor *accelerometerSensor;
    ASensorEventQueue *sensorEventQueue;

    // Objects
    std::unique_ptr<Triangle> triangle;
    std::unique_ptr<Square> square;

    std::unique_ptr<gvr::GvrApi> gvrApi;

    /**
     * 交换链，用于交换帧缓冲区交换
     */
    std::unique_ptr<gvr::SwapChain> swapChain;
    /**
     * 二级缓冲区
     */
    gvr::BufferViewport scratchVP;
    /**
     * 视口缓冲区列表
     */
    std::unique_ptr<gvr::BufferViewportList> vpList;

    /**
     * gl 初始化
     * 必须在渲染线程调用
     */
    void initializeGL();
    void initObjects();

    // vr mode
    void drawEye(const gvr::Rectf &sourceUv, const gvr::Mat4f &eyeMat);

public:
    /**
     * 构造函数
     * @param jgvrCtx java google vr context
     */
    Engine(jlong jGvrCtx);

    /**
     * 引擎初始化
     */
    void init();

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
