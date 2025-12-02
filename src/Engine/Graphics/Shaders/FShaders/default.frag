#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoords;
in vec3 normal;
in vec3 worldPosition;

uniform sampler2D texture0;

void main() {
    float ambient_lighting = 0.20f;

    FragColor = texture(texture0, texCoords);
}