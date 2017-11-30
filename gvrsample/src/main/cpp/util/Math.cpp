//
// Created by michael on 17-11-30.
//

#include "Math.h"

namespace math {
    gvr::Rectf ModulateRect(const gvr::Rectf &rect, float width, float height) {
        gvr::Rectf result = {rect.left * width, rect.right * width,
                             rect.bottom * height, rect.top * height};
        return result;
    }

    gvr::Recti CalculatePixelSpaceRect(const gvr::Sizei &textureSize,
                                              const gvr::Rectf &textureRect) {
        const float width = static_cast<float>(textureSize.width);
        const float height = static_cast<float>(textureSize.height);
        const gvr::Rectf rect = ModulateRect(textureRect, width, height);
        const gvr::Recti result = {
                static_cast<int>(rect.left), static_cast<int>(rect.right),
                static_cast<int>(rect.bottom), static_cast<int>(rect.top)};
        return result;
    }
}

gvr::Mat4f Math::matrixMult(const gvr::Mat4f &mat1, const gvr::Mat4f &mat2) {
    gvr::Mat4f result = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += mat1.m[i][k] * mat2.m[k][j];
            }
        }
    }
    return result;
}
