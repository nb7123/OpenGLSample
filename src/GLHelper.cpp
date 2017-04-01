//
// Created by michael on 17-4-1.
//

#include <fstream>
#include <iostream>
#include <SOIL.h>
#include "GLHelper.h"

std::string GLHelper::load_src(const char *file) {
    std::string result;

    std::ifstream in;
    in.open(file);

    if (in.is_open()) {
        char buffer[1024];
        while (!in.eof()) {
            result.append("\n");

            in.getline(buffer, sizeof(buffer));
            result.append(buffer);
        }
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
    glGenerateMipmap(GL_IMAGE_2D);

    // free data
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
