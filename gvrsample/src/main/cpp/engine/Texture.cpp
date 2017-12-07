//
// Created by michael on 17-12-7.
//

#include <memory>
#include <GLES3/gl3.h>
#include "Texture.h"
#include "../util/asset/Asset.h"
#include "../util/soil/SOIL.h"
#include "../util/Log.h"

Texture::Texture(const char *path) {
    // 加载texture
    std::shared_ptr<Asset> asset = Asset::open(path);
    unsigned char* texImage = SOIL_load_image_from_memory(
            (const unsigned char *const) asset->readContent(),
            asset->contentLength(),
            &width, &height, NULL, SOIL_LOAD_RGBA);
    Log::i(__func__, "Load image complete, data length[%d]", asset -> contentLength());

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texImage);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(texImage);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    Log::i(__func__, "Texture release");
}
