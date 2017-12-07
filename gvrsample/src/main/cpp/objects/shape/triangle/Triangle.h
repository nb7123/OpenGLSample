//
// Created by michael on 17-12-1.
//

#ifndef OPENGLSAMPLE_TRIANGLE_H
#define OPENGLSAMPLE_TRIANGLE_H


#include <GLES3/gl3.h>
#include "../../Object.h"

class Triangle: public Object {
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
    const std::string srcV();
    const std::string srcF();

    void draw();
};


#endif //OPENGLSAMPLE_TRIANGLE_H
