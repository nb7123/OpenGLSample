//
// Created by michael on 17-12-1.
//

#ifndef OPENGLSAMPLE_OBJECT_H
#define OPENGLSAMPLE_OBJECT_H


#include <GLES3/gl3.h>
#include <string>

class Object {
private:
    GLuint program;
    GLuint shaderV;
    GLuint shaderF;

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

public:
    /**
     * 初始化
     */
    void init();
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
    void useProgram();

    /**
     * 绘制自己
     */
    virtual void draw() = 0;

    virtual ~Object();
};


#endif //OPENGLSAMPLE_OBJECT_H
