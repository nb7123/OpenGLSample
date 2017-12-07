//
// Created by michael on 17-12-7.
//

#include <android/asset_manager_jni.h>
#include "AssetManager.h"

AAssetManager *AssetManager::assetMgr = NULL;
void AssetManager::init(JNIEnv *env, jobject assetMgr) {
    AssetManager::assetMgr = AAssetManager_fromJava(env, assetMgr);
}