//
// Created by michael on 17-12-7.
//

#include <cstdlib>
#include <android/asset_manager_jni.h>
#include "Asset.h"
#include "../Log.h"
#include "AssetManager.h"

Asset::Asset(AAsset *aasset): aasset(aasset) {

}

Asset::~Asset() {
    AAsset_close(aasset);
    aasset = NULL;
}

std::shared_ptr<Asset> Asset::open(const char *path, int mode) {
    AAsset *asset = AAssetManager_open(AssetManager::assetMgr, path, mode);
    return std::shared_ptr<Asset>(new Asset(asset));
}

const char *Asset::readLine() {

    return nullptr;
}

const std::string &Asset::readShaderSrc() {
    std::string src;
    src.append((char *)readContent(), (unsigned int) contentLength());

    return src;
}

const void *Asset::readContent() {
    return AAsset_getBuffer(aasset);
}

int Asset::contentLength() {
    return AAsset_getLength(aasset);
}

