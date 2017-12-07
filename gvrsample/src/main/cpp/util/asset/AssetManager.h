//
// Created by michael on 17-12-7.
//

#ifndef OPENGLSAMPLE_ASSETMANAGER_H
#define OPENGLSAMPLE_ASSETMANAGER_H


#include <android/asset_manager.h>
#include <jni.h>

class AssetManager {
public:
    static AAssetManager *assetMgr;
    static void init(JNIEnv *env, jobject assetMgr);
};


#endif //OPENGLSAMPLE_ASSETMANAGER_H
