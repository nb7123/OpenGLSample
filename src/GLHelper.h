//
// Created by michael on 17-4-1.
//

#ifndef OPENGLSAMPLE_GLHELPER_H
#define OPENGLSAMPLE_GLHELPER_H


#include <string>
#include <GL/glew.h>

class GLHelper {
public:
    static std::string load_src(const char *file);
    static GLuint load_texture(const char *file,     // image file
                               int channels,         // image channel
                               GLint internalformat, // image internal format
                               GLenum format         // image format
             );
};


#endif //OPENGLSAMPLE_GLHELPER_H
