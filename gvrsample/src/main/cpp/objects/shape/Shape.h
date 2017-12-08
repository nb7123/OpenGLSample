//
// Created by michael on 17-12-8.
//

#ifndef OPENGLSAMPLE_SHAPE_H
#define OPENGLSAMPLE_SHAPE_H

#include <string>
#include "../Object.h"

class Shape: public Object {
    const std::string srcV();
    const std::string srcF();
};


#endif //OPENGLSAMPLE_SHAPE_H
