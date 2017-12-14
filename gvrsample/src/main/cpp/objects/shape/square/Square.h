//
// Created by michael on 17-12-6.
//

#ifndef OPENGLSAMPLE_SQUARE_H
#define OPENGLSAMPLE_SQUARE_H


#include <bits/unique_ptr.h>
#include "../../Object.h"
#include "../../../engine/Texture.h"
#include "../Shape.h"

class Square: public Shape {
private:
    std::unique_ptr<Texture> texture0;
    std::unique_ptr<Texture> texture1;

    GLint locTex0;
    GLint locTex1;

    void transformation();
public:
    void init();
    void draw();
    ~Square();
};


#endif //OPENGLSAMPLE_SQUARE_H
