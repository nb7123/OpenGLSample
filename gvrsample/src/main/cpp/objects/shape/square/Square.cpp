//
// Created by michael on 17-12-6.
//

#include "Square.h"

const char *Square::LOG_TAG = "Square";
const char *Square::shaderSrcV =
        "#version 310 es\n"
                "layout (location = 0) in vec3 position;\n"
                "void main() {\n"
                "   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
                "}";
const char *Square::shaderSrcF =
        "#version 310 es\n"
                "mediump out vec4 color;\n"
                "void main() {\n"
                "   color = vec4(1.0f, 0.5f, 1.0f, 1.0f);\n"
                "}";

const GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
};

const GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
};

void Square::draw() {
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    useProgram();
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *) 0);

    // draw
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
    // unbind
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

const char *Square::srcV() {
    return shaderSrcV;
}

const char *Square::srcF() {
    return shaderSrcF;
}
