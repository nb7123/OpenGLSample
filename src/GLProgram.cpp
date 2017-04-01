//
// Created by michael on 17-4-1.
//

#include <string>
#include <cstring>
#include <iostream>
#include "GLProgram.h"
#include "GLHelper.h"

void checkCompileStatus(GLuint shader) {

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success) {
        std::cout << "Compile shader success, shader id: " << shader << std::endl;
    } else {
        char buf[1024];
        memset(buf, 0, sizeof(buf));

        glGetShaderInfoLog(shader, sizeof(buf), nullptr, buf);
        std::cout << "Compile shader error: " << buf << std::endl;
    }
}

void checkLinkStatus(GLuint program) {
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (success) {
        std::cout << "Program link success, id: " << program << std::endl;
    } else {
        char buf[1024];
        glGetProgramInfoLog(program, sizeof(buf), nullptr, buf);

        std::cout << "Program link failed, error: " << buf << std::endl;
    }
}

GLProgram::GLProgram(const char *v_GLSL_f, const char *f_GLSL_f) {
    std::string vs = GLHelper::load_src(v_GLSL_f);
    const char *vss = vs.c_str();

    std::string fs = GLHelper::load_src(f_GLSL_f);
    const char *fss = fs.c_str();

    GLuint v = glCreateShader(GL_VERTEX_SHADER);
    GLuint f = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(v, 1, &vss, 0);
    glShaderSource(f, 1, &fss, 0);

    glCompileShader(v);
    checkCompileStatus(v);

    glCompileShader(f);
    checkCompileStatus(f);

    program = glCreateProgram();
    glAttachShader(program, v);
    glAttachShader(program, f);
    glLinkProgram(program);
    checkLinkStatus(program);
}

GLuint GLProgram::id() {
    return program;
}

void GLProgram::use() {
    glUseProgram(program);
}
