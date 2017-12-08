//
// Created by michael on 17-12-1.
//

#ifndef OPENGLSAMPLE_TRIANGLE_H
#define OPENGLSAMPLE_TRIANGLE_H


#include <GLES3/gl3.h>
#include "../../Object.h"
#include "../Shape.h"

class Triangle: public Shape {
private:
    /**
     * 下面这样一个三角形的顶点
     *          ×
     *         ×××
     *        ××*××
     *       ×××××××
     *      ×××××××××
     */
    static const GLfloat vertices[];

public:
    void draw();
};


#endif //OPENGLSAMPLE_TRIANGLE_H
