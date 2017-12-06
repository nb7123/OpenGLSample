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

    /**
     * 顶点着色器
     */
    static const char *shaderV;

    /**
     * 片段着色器
     */
    static const char *shaderF;


public:
    const char *srcV();
    const char *srcF();

    void draw();
};


#endif //OPENGLSAMPLE_TRIANGLE_H
