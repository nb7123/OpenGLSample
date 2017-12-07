//
// Created by michael on 17-12-1.
//

#include "Triangle.h"
#include "../../../util/asset/Asset.h"

const GLfloat Triangle::vertices[]  = {
        -0.5f, -0.5f, 0.0,
        0.5,  -0.5f, 0.0,
        0,0,   0.5 , 0,0
};


const std::string Triangle::srcV() {
    std::shared_ptr<Asset> asset = Asset::open("shader/triangle_v.glsl", AASSET_MODE_BUFFER);

    return asset->readShaderSrc();
}

const std::string Triangle::srcF() {
    std::shared_ptr<Asset> asset = Asset::open("shader/triangle_f.glsl", AASSET_MODE_BUFFER);

    return asset->readShaderSrc();
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

