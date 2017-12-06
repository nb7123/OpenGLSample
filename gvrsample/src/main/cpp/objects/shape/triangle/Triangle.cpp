//
// Created by michael on 17-12-1.
//

#include "Triangle.h"

const GLfloat Triangle::vertices[]  = {
        -0.5f, -0.5f, 0.0,
        0.5,  -0.5f, 0.0,
        0,0,   0.5 , 0,0
};

const char *Triangle::shaderV =
        "#version 310 es\n"
                "layout (location = 0) in vec3 position;\n"
                "void main() {\n"
                "   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
                "}";

const char *Triangle::shaderF =
        "#version 310 es\n"
                "mediump out vec4 color;\n"
                "void main() {\n"
                "   color = vec4(0.0f, 0.5f, 1.0f, 1.0f);\n"
                "}";


const char *Triangle::srcV() {
    return Triangle::shaderV;
}

const char *Triangle::srcF() {
    return Triangle::shaderF;
}

void Triangle::draw() {
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    useProgram();
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

