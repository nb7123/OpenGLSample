#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 in_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 tex_coord;

void main() {
    gl_Position = projection  * model * vec4(pos, 1.0f);
    tex_coord = in_coord;
}
