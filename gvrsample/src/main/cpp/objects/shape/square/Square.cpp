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

Square::~Square() {
    Log::i(__func__, "Release data");
}

void Square::draw() {
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // transformation
    glUniformMatrix4fv(locTrans, 1, GL_FALSE, translate.data());

    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0->texture);
    glUniform1i(locTex0, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1->texture);
    glUniform1i(locTex1, 1);

    use();
    glBindVertexArray(vao);

    const int stride = 8 * sizeof(GLfloat);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    // draw
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
    // unbind
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Square::init() {
    Object::init();

    //    const char* path = "img/img_cheryl.jpg";
    const char* path = "img/ic_launcher.png";
    texture0 = std::unique_ptr<Texture>(new Texture(path));
    texture1 = std::unique_ptr<Texture>(new Texture("img/img_cheryl.jpg"));

    locTex0 = glGetUniformLocation(program, "tex2D0");
    locTex1 = glGetUniformLocation(program, "tex2D1");

    std::string data;
    for (int i = 0; i < translate.size();) {
        for (int j = 0; j < 4; ++j, ++i) {

        }
    }
}
