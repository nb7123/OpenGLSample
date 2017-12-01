//
// Created by michael on 17-11-28.
//
#include <EGL/egl.h>

#include <android_native_app_glue.h>
#include <string>

#include "engine/Engine.h"

/**
 * android 应用主入口函数
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 * @param app android app上下文
 */
void android_main(struct android_app *app) {
    // engine
    Engine *engine = Engine::getInstance(app);
    while (true) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source *source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident = ALooper_pollAll(0, NULL, &events,
                                        (void **) &source)) >= 0) {
            // Process this event.
            if (source != NULL) {
                source->process(app, source);
            }

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER) {
                engine->pullAccelerometerEvent();
            }

            // Check if we are exiting.
            if (app->destroyRequested != 0) {
                delete engine;
                return;
            }
        }

        std::string str = "Hello";

        engine->draw();
    }
}