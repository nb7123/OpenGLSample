#version 310 es

mediump in vec3 vOutColor;
mediump in vec2 vOutTexPos;

mediump out vec4 color;

uniform sampler2D tex2D;

void main() {
    color = texture(tex2D, vOutTexPos);
//    color = vec4(vOutTexPos, 1.0f, 1.0f);
}
