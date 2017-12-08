//
// Created by michael on 17-12-1.
//

#ifndef OPENGLSAMPLE_OBJECT_H
#define OPENGLSAMPLE_OBJECT_H


#include <GLES3/gl3.h>
#include <string>
#include <vector>

class Object {
private:
    /**
     * 加载着色器
     * @param shaderType    着色器类型
     */
    GLuint loadShader(GLint shaderType);
    /**
     * 创建着色器程序
     * @return
     */
    void createProgram();

protected:
    GLuint program;

    std::vector<GLfloat> translate;
    std::vector<GLfloat> scale;
    std::vector<GLfloat> rotation;

    GLint locTrans;
    GLint locScale;
    GLint locRotat;

public:
    Object();
    /**
     * 初始化
     */
    virtual void init();
    /**
     * 顶点着色器源代码
     * @return 顶点着色器源代码
     */
    virtual const std::string srcV() = 0;
    /**
     * 片断着色器源代码
     * @return 片断着色器源代码
     */
    virtual const std::string srcF() = 0;

    /**
     * 获取着色器日志
     * @param shader 着色器
     * @return       日志信息
     */
    std::string getShaderInfoLog(GLuint shader);
    /**
     * 获取着色器程序日志信息
     * @param program   着色器程序
     * @return          日志信息
     */
    std::string getProgramInfoLog(GLuint program);

    /**
     * 使用着色器程序绘制
     */
    void use();

    /**
     * 绘制自己
     */
    virtual void draw() = 0;

    virtual ~Object();
};


#endif //OPENGLSAMPLE_OBJECT_H
