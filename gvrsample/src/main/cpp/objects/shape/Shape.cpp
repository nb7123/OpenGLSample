//
// Created by michael on 17-12-8.
//

#include "Shape.h"
#include "../../util/asset/Asset.h"

const std::string Shape::srcV() {
    std::shared_ptr<Asset> asset = Asset::open("shader/triangle_v.glsl", AASSET_MODE_BUFFER);

    return asset->readShaderSrc();
}

const std::string Shape::srcF() {
    std::shared_ptr<Asset> asset = Asset::open("shader/triangle_f.glsl", AASSET_MODE_BUFFER);

    return asset->readShaderSrc();
}
