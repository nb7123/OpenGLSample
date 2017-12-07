//
// Created by michael on 17-12-1.
//

#include <string>
#include <iostream>
#include <cstdlib>

#include "Object.h"
#include "../util/Log.h"

GLuint Object::loadShader(GLint shaderType) {
    std::string src;
    std::string typeName;
    if (shaderType == GL_VERTEX_SHADER) {
        src = srcV();
        typeName = "Vertex shader";
    } else {
        src = srcF();
        typeName = "Fragment shader";
    }

    GLuint shader = glCreateShader(shaderType);
    // 加载着色器源码
    const char *srcData = src.data();
    glShaderSource(shader, 1, &srcData, NULL);

    // 编译着色器
    glCompileShader(shader);

    // 查询编译结果
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::string clazzName = "Object";
        std::string infoLog = getShaderInfoLog(shader);
        Log::e(clazzName.c_str(), "Shader compile failed,\nInfo log: %s", infoLog.c_str());

        // 删除着色器
        glDeleteShader(shader);
        shader = 0;
    }

    return shader;
}

void Object::createProgram() {
    shaderV = loadShader(GL_VERTEX_SHADER);
    shaderF = loadShader(GL_FRAGMENT_SHADER);

    if (shaderV == 0 || shaderF == 0) {
        Log::e(__func__, "Some shader load failed!");
    } else {
        program = glCreateProgram();
        glAttachShader(program, shaderV);
        glAttachShader(program, shaderF);
        // 链接着色器
        glLinkProgram(program);

        // 查询链接结果信息
        // 查询编译结果
        GLint success = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            std::string clazzName = "Object";

            std::string infoLog = getProgramInfoLog(program);
            Log::e(clazzName.c_str(), "Program link failed,\nInfo log: %s", infoLog.c_str());

            // 删除着色器程序
            glDeleteProgram(program);
            program = 0;
        }
    }
}

std::string Object::getShaderInfoLog(GLuint shader) {
    GLchar *infoLog;
    // 先查询日志长度
    GLsizei infoLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
    // 查询日志信息
    infoLog = (char *) malloc((size_t) infoLength);
    memset(infoLog, 0, (size_t) infoLength);
    glGetShaderInfoLog(shader, infoLength, NULL, infoLog);

    return std::string(infoLog);
}

std::string Object::getProgramInfoLog(GLuint program) {
    GLchar *infoLog;
    // 先查询日志长度
    GLsizei infoLength = 0;
    glGetProgramInfoLog(program, 0, &infoLength, NULL);
    // 根本相应长度查询日志
    infoLength += 1;
    infoLog = (char *) malloc((size_t) infoLength);
    memset(infoLog, 0, (size_t) infoLength);
    glGetProgramInfoLog(program, infoLength, NULL, infoLog);

    return std::string(infoLog);
}

void Object::useProgram() {
    glUseProgram(program);
}

Object::~Object() {
    Log::i(__func__, "Release data");
    glDeleteShader(shaderV);
    glDeleteShader(shaderF);
    glDeleteProgram(program);
}

void Object::init() {
    createProgram();
}
