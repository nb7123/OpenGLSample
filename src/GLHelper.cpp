//
// Created by michael on 17-4-1.
//

#include <fstream>
#include <iostream>
#include "GLHelper.h"

std::string GLHelper::load_src(const char *file) {
    std::string result;

    std::ifstream in;
    in.open(file);

    if (in.is_open()) {
        while (!in.eof()) {
            result.append("\n");
            result.append(in.getline())
        }
    } else {
        std::cout << "Open file [" << file << "] error!" << std::endl;
    }

    return result;
}
