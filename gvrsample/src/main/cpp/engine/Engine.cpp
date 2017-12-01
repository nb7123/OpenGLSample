//
// Created by michael on 17-11-28.
//

#include <cstdlib>
#include <time.h>
#include <memory>
#include <bits/unique_ptr.h>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include "Engine.h"
#include "../util/Log.h"
#include "../util/Math.h"

/**
 * 绘制眼睛
 * @param sourceUv
 * @param eyeMat
 */
void Engine::drawEye(const gvr::Rectf &sourceUv, const gvr::Mat4f &eyeMat) {
    triangle -> draw();
}

/**
 * 绘制背景
 */
void drawBackground() {
    time_t t = time(NULL);

    srand(t);
    GLfloat r = (GLfloat) (rand() % 255 / 255.0);
    GLfloat g = (GLfloat) (rand() % 255 / 255.0);
    GLfloat b = (GLfloat) (rand() % 255 / 255.0);

    glClearColor(r, g, b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

const char *Engine::LOG_TAG = "Engine";

Engine::Engine(jlong jGvrCtx) {
    // 将JAVA持有指针转换存储到此
    gvrApi = gvr::GvrApi::WrapNonOwned(reinterpret_cast<gvr_context *>(jGvrCtx));

    Log::d(LOG_TAG, "Create engine with: %lld", jGvrCtx);

    // 创建缓冲区对象
    scratchVP = gvrApi->CreateBufferViewport();
}

Engine::~Engine() {
    release();
}

void Engine::release() {
}

void Engine::init() {
    initializeGL();
    initObjects();
}

void Engine::initializeGL() {
    gvrApi->InitializeGl();

    Log::d(LOG_TAG, "Native gl initialized");

    // 创建帧缓冲区链
    std::vector<gvr::BufferSpec> specs;
    specs.push_back(gvrApi->CreateBufferSpec());
    swapChain.reset(new gvr::SwapChain(gvrApi->CreateSwapChain(specs)));
    // 创建视口（View port）列表
    vpList.reset(new gvr::BufferViewportList(gvrApi->CreateEmptyBufferViewportList()));

    // create object
}

void Engine::initObjects() {
    triangle = std::unique_ptr<Triangle>(new Triangle());
}

void Engine::draw() {
    gvr::Sizei maxSize = gvrApi->GetMaximumEffectiveRenderTargetSize();
    maxSize.width /= 4;
    maxSize.height /= 2;
    swapChain->ResizeBuffer(0, maxSize);
    // 设置到最佳视口大小
    vpList->SetToRecommendedBufferViewports();
    // 获取一个帧
    gvr::Frame frame = swapChain->AcquireFrame();

    // 预测下一时间点
    gvr::ClockTimePoint timePoint = gvr::GvrApi::GetTimePointNow();
    timePoint.monotonic_system_time_nanos += kPredictionTimeWithoutVsyncNanos;
    // 获取最近一次的预测的头部位置的投影矩阵
    gvr::Mat4f headMat = gvrApi->GetHeadSpaceFromStartSpaceRotation(timePoint);
    // 左右眼相的投影矩阵
    // 将投影矩阵从眼睛空间转换到头部空间
    gvr::Mat4f lEyeMat = Math::matrixMult(gvrApi->GetEyeFromHeadMatrix(GVR_LEFT_EYE), headMat);
    gvr::Mat4f rEyeMat = Math::matrixMult(gvrApi->GetEyeFromHeadMatrix(GVR_RIGHT_EYE), headMat);

    // 绑定缓冲区
    // 渲染每一只眼睛的场景到帧缓冲区
    // 解除绑定
    // 提交到畸变空间
    frame.BindBuffer(0);
    drawBackground();
    vpList->GetBufferViewport(GVR_LEFT_EYE, &scratchVP);
    gvr::Recti pixelRect = math::CalculatePixelSpaceRect(maxSize, scratchVP.GetSourceUv());
    Log::i(LOG_TAG, "Left eye pixel rect(left: %d, bottom: %d, width: %d, height: %d",
           pixelRect.left, pixelRect.bottom,
            pixelRect.right - pixelRect.left,
            pixelRect.top - pixelRect.bottom);
    glViewport(pixelRect.left, pixelRect.bottom,
               pixelRect.right - pixelRect.left, pixelRect.top - pixelRect.bottom);
    drawEye(scratchVP.GetSourceUv(), lEyeMat);
    vpList->GetBufferViewport(GVR_RIGHT_EYE, &scratchVP);
    pixelRect = math::CalculatePixelSpaceRect(maxSize, scratchVP.GetSourceUv());
    Log::i(LOG_TAG, "Right eye pixel rect(left: %d, bottom: %d, width: %d, height: %d",
           pixelRect.left, pixelRect.bottom,
           pixelRect.right - pixelRect.left,
           pixelRect.top - pixelRect.bottom);
    glViewport(pixelRect.left, pixelRect.bottom,
               pixelRect.right - pixelRect.left, pixelRect.top - pixelRect.bottom);
    drawEye(scratchVP.GetSourceUv(), rEyeMat);
    frame.Unbind();
    frame.Submit(*vpList, headMat);
}

void Engine::pullAccelerometerEvent() {
    ASensorEvent event;
    while (ASensorEventQueue_getEvents(sensorEventQueue,
                                       &event, 1) > 0) {
        Log::i(LOG_TAG, "accelerometer: x=%f y=%f z=%f",
             event.acceleration.x, event.acceleration.y,
             event.acceleration.z);
    }
}

