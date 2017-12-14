//
// Created by michael on 17-12-14.
//

#include <array>
#include <cmath>
#include "GLHelper.h"

std::array<GLfloat, 16>
GLHelper::perspectiveMatFromFOV(gvr::Rectf fov, const float z_near, const float z_far) {
    std::array<GLfloat, 16> result;
    const float x_left = (const float) (-std::tan(fov.left * M_PI / 180.0f) * z_near);
    const float x_right = (const float) (std::tan(fov.right * M_PI / 180.0f) * z_near);
    const float y_bottom = (const float) (-std::tan(fov.bottom * M_PI / 180.0f) * z_near);
    const float y_top = (const float) (std::tan(fov.top * M_PI / 180.0f) * z_near);
    const float zero = 0.0f;

    assert(x_left < x_right && y_bottom < y_top && z_near < z_far &&
           z_near > zero && z_far > zero);
    const float X = (2 * z_near) / (x_right - x_left);
    const float Y = (2 * z_near) / (y_top - y_bottom);
    const float A = (x_right + x_left) / (x_right - x_left);
    const float B = (y_top + y_bottom) / (y_top - y_bottom);
    const float C = (z_near + z_far) / (z_near - z_far);
    const float D = (2 * z_near * z_far) / (z_near - z_far);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i*4+j] = 0.0f;
        }
    }
    result[0] = X;
    result[2] = A;
    result[1*4+1] = Y;
    result[1*4+2] = B;
    result[2*4+2] = C;
    result[2*4+3] = D;
    result[3*4+2] = -1;

    return result;
}
