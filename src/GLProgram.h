//
// Created by michael on 17-4-1.
//

#ifndef OPENGLSAMPLE_GLPROGRAM_H
#define OPENGLSAMPLE_GLPROGRAM_H


#include <GL/glew.h>

class GLProgram {
private:
    GLuint program;

public:
    GLProgram(const char *v_GLSL_f,  //  vertex GLSL file
              const char *f_GLSL_f   //  fragment FLSL file
    );

    /**
     * this program id
     * @return  program id
     */
    GLuint id();

    /**
     * use this program
     */
    void use();
};


#endif //OPENGLSAMPLE_GLPROGRAM_H
