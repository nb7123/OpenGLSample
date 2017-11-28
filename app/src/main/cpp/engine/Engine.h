//
// Created by michael on 17-11-28.
//

#ifndef OPENGLSAMPLE_ENGINE_H
#define OPENGLSAMPLE_ENGINE_H


#include <EGL/egl.h>

class Engine {
private:
    static const char *LOG_TAG;
    static void handle_cmd(struct android_app *app, int32_t cmd);

    static Engine *instance;

    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;

    Engine(struct android_app *app);

public:

    static Engine *getInstance(struct android_app *app) {
        if (nullptr == instance) {
            instance = new Engine(app);
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
     * 手动释放资源
     */
    void release();

    ~Engine();
};


#endif //OPENGLSAMPLE_ENGINE_H
