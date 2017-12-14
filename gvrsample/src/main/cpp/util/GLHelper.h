//
// Created by michael on 17-12-14.
//

#ifndef OPENGLSAMPLE_GLHELPER_H
#define OPENGLSAMPLE_GLHELPER_H

#import <GLES3/gl3.h>
#import <array>
#include <vr/gvr/capi/include/gvr_types.h>


class GLHelper {
public:
    static std::array<GLfloat , 16> perspectiveMatFromFOV(gvr::Rectf fov, const float near, const float far);
};


#endif //OPENGLSAMPLE_GLHELPER_H
