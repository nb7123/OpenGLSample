//
// Created by michael on 17-12-6.
//

#ifndef OPENGLSAMPLE_SQUARE_H
#define OPENGLSAMPLE_SQUARE_H


#include "../../Object.h"

class Square: public Object {
private:
    static const char* LOG_TAG;
    static const char* shaderSrcV;
    static const char* shaderSrcF;

public:
    void draw();
    const char* srcV();
    const char* srcF();
};


#endif //OPENGLSAMPLE_SQUARE_H
