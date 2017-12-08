#version 310 es

uniform mat4 translate;
uniform mat4 scale;
uniform mat4 rotation;
uniform mat4 projection;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texPos;

out vec3 vOutColor;
out vec2 vOutTexPos;

void main() {
    gl_Position = translate * vec4(position.xyz, 1.0f);
    vOutColor = color;
    vOutTexPos = vec2(texPos.x, 1.0f - texPos.y);
}
