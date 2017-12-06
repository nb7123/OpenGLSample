//
// Created by michael on 17-4-1.
//

#include <fstream>
#include <iostream>
#include <SOIL.h>
#include <sstream>
#include "GLHelper.h"

std::string GLHelper::load_src(const char *file) {
    std::string result;

    std::ifstream in;
    in.open(file);

    if (in.is_open()) {
        std::stringstream stringstream;
        stringstream << in.rdbuf();
        result = stringstream.str();
        in.close();
    } else {
        std::cout << "Open file [" << file << "] error!" << std::endl;
    }

    return result;
}

GLuint GLHelper::load_texture(const char *file,     // image file
                              int channels,         // image channel
                              GLint internalformat, // image internal format
                              GLenum format         // image format
) {
    int w, h;
    unsigned char *image = SOIL_load_image(file, &w, &h, 0, channels);

    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, internalformat, w, h, 0, format, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // free data
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
