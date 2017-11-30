//
// Created by michael on 17-11-30.
//

#ifndef OPENGLSAMPLE_MATH_H
#define OPENGLSAMPLE_MATH_H

#include <vr/gvr/capi/include/gvr.h>


class Math {

public:
        static gvr::Mat4f matrixMult(const gvr::Mat4f &mat1, const gvr::Mat4f &mat2);

};


#endif //OPENGLSAMPLE_MATH_H
