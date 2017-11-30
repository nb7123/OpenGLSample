//
// Created by michael on 17-11-30.
//

#include "Math.h"

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
