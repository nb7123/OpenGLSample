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
        "#version 330 core;"
                "layout (location = 0) in vec3 position;"
                "void main() {"
                "gl_Position = vec4(position.x, position.y, position.z, 1.0);"
                "}";

const char *Triangle::shaderF =
        "#version 330 core;"
                "out vec4 color;"
                "void main() {"
                "   color = vec4(1.0f, 0.5f, 1.0f, 1.0f);"
                "}";


const char *Triangle::srcV() {
    return Triangle::shaderV;
}

const char *Triangle::srcF() {
    return Triangle::shaderF;
}

void Triangle::draw() {
    useProgram();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}

