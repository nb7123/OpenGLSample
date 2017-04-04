#version 330 core

in vec2 tex_coord;
in vec3 Normal;
in vec3 frag_pos;

uniform sampler2D tex0;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 camera_pos;

out vec4 color;

void main() {
    vec3 objColor = vec3(1.0f, 0.0f, 0.0f);

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * light_color;
    vec3 nor = normalize(Normal);
    vec3 lightDirt = normalize(light_pos - frag_pos);

    float diff = max(dot(nor, lightDirt), 0.0f);
    vec3 diffUse = diff * light_color;

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(camera_pos - frag_pos);
    vec3 reflectDir = reflect(-lightDirt, nor);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * light_color;

    vec3 result = (ambient + diffUse + specular) * vec3(objColor);
    color = vec4(result, 1.0f);
}
