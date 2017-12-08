//
// Created by michael on 17-12-7.
//

#ifndef OPENGLSAMPLE_ASSET_H
#define OPENGLSAMPLE_ASSET_H


#include <bits/unique_ptr.h>
#include <memory>
#include <android/asset_manager.h>
#include <jni.h>

class Asset {
private:
    AAsset *aasset;
    Asset(AAsset *aasset);
public:
    /**
     * 打开一个Asset文件
     * @param path  文件路径
     * @param mode  打开方式
     * @return      Asset指针
     */
    static std::shared_ptr<Asset> open(const char *path, int mode = AASSET_MODE_BUFFER);

    /**
     * 将Asset作为着色器文件读取
     * @return  着色器源码
     */
    const std::string readShaderSrc();
    /**
     * 读取内容
     * @return       数据指针
     */
    const void* readContent();
    /**
     * 数据长度
     * @return
     */
    int contentLength();

    /**
     * 读取一行数据
     * @return  一行数据的字节数
     */
    const char *readLine();

    ~Asset();
};


#endif //OPENGLSAMPLE_ASSET_H
