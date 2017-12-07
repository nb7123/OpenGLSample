//
// Created by michael on 17-12-6.
//

#include <android/asset_manager.h>
#include "Square.h"
#include "../../../util/asset/Asset.h"
#include "../../../util/Log.h"

const GLfloat vertices[] = {
        // --位置           -- 颜色            -- 贴图
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
};

const GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
};

Square::Square() {
    const char* path = "img/img_chery1.jpg";
    texture = std::unique_ptr<Texture>(new Texture(path));
}

Square::~Square() {
    Log::i(__func__, "Release data");
}

void Square::draw() {
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    useProgram();
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, texture->texture);
    const int stride = 8 * sizeof(GLfloat);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    // draw
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
    // unbind
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

const std::string Square::srcV() {
    std::shared_ptr<Asset> asset = Asset::open("shader/triangle_v.glsl", AASSET_MODE_BUFFER);

    return asset->readShaderSrc();
}

const std::string Square::srcF() {
    std::shared_ptr<Asset> asset = Asset::open("shader/triangle_f.glsl", AASSET_MODE_BUFFER);

    return asset->readShaderSrc();
}
