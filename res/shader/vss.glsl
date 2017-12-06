#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 in_coord;
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 tex_coord;
out vec3 Normal;
out vec3 frag_pos;

void main() {
    gl_Position = projection  * view * model * vec4(pos, 1.0f);
    tex_coord = vec2(in_coord.x, 1 - in_coord.y);

    frag_pos = vec3(gl_Position);
    Normal = normal;
}
