//
// Created by michael on 17-12-6.
//

#ifndef OPENGLSAMPLE_SQUARE_H
#define OPENGLSAMPLE_SQUARE_H


#include <bits/unique_ptr.h>
#include "../../Object.h"
#include "../../../engine/Texture.h"

class Square: public Object {
private:
    std::unique_ptr<Texture> texture;
public:
    Square();
    void draw();
    const std::string srcV();
    const std::string srcF();
    ~Square();
};


#endif //OPENGLSAMPLE_SQUARE_H
