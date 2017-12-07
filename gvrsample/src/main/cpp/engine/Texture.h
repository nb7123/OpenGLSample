//
// Created by michael on 17-12-7.
//

#ifndef OPENGLSAMPLE_TEXTURE_H
#define OPENGLSAMPLE_TEXTURE_H


class Texture {
public:
    int width;
    int height;
    GLuint texture;
    int textureId;

    Texture(const char* path);
    virtual ~Texture();
};


#endif //OPENGLSAMPLE_TEXTURE_H
