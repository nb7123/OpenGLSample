#include <iostream>

//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SOIL.h>
#include <fstream>
#include "GLProgram.h"
#include "GLHelper.h"
#include "../res/Cube.h"

GLFWwindow *window;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool key_state[1024];
const GLfloat speed = 0.05f;

void initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(400, 400, "Window", nullptr, nullptr);
    if (nullptr == window) {
        std::cout << "Create window failed！" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    // view port
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

//    glfwSetKeyCallback(window, key_callback);

    // init glew
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Init glew failed, exit!" << std::cout;
        exit(-1);
    }
}

int main() {
    initWindow();

    const GLubyte *vendor = glGetString(GL_VENDOR);
    std::cout << "Vendor: " << vendor << std::endl;
    const GLubyte *version = glGetString(GL_VERSION);
    std::cout << "GL version: " << version << std::endl;

    GLuint vao, vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLProgram program(
            "/home/michael/CLionProjects/OpenGLSample/res/shader/vss.glsl",
            "/home/michael/CLionProjects/OpenGLSample/res/shader/fss.glsl"
    );

    GLuint texture = GLHelper::load_texture(
            "/home/michael/CLionProjects/OpenGLSample/res/sample.png",
            SOIL_LOAD_RGBA,
            GL_RGBA, GL_RGBA
    );

    glm::mat4 model;
    model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 view;
    view = glm::rotate(glm::mat4(), glm::radians(45.0f), glm::vec3(1.0f, 0.5f, 1.0f));

    glm::mat4 projection;
    projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.5f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.use();

        glUniformMatrix4fv(
                glGetUniformLocation(program.id(), "model"),
                1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(
                glGetUniformLocation(program.id(), "view"),
                1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(
                glGetUniformLocation(program.id(), "projection"),
                1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D, texture);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
