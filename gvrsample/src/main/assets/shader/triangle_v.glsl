#version 310 es

// 局部坐标到世界坐标的转换，可以通过变换实现
// 变换需要的矩阵
uniform mat4 translateView; // 平移矩阵
uniform mat4 scaleView;     // 缩放矩阵
uniform mat4 rotationView;  // 旋转矩阵

// 世界坐标->眼睛坐标（view space）
uniform mat4 eyeView;
// 眼睛坐标（view space）->投影坐标
uniform mat4 projView;

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texPos;

out vec2 vOutTexPos;

void main() {
    // 局部坐标->世界坐标
    mat4 modelView = translateView * rotationView * scaleView;

    gl_Position = projView * vec4(position, 1.0f);
    vOutTexPos = vec2(texPos.x, 1.0f - texPos.y);
}
