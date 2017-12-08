#version 310 es

mediump in vec3 vOutColor;
mediump in vec2 vOutTexPos;

mediump out vec4 color;

uniform sampler2D tex2D0;
uniform sampler2D tex2D1;

void main() {
    color = mix(texture(tex2D0, vOutTexPos), texture(tex2D1, vOutTexPos), 0.8f);
}
