#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 textureCoordinates;
in vec3 normal;
in vec3 worldPosition;

uniform sampler2D texture0;

uniform vec3 light_color;
uniform vec3 light_position;

void main(  ) {
    float ambient_strength = 0.20;
    float light_dir = max(dot(normal, normalize(light_position - worldPosition)), 0);

    vec3 ambient_lighting = ambient_strength * light_color;
    vec3 diffuse = light_dir * light_color;

    vec3 result = (ambient_lighting + diffuse) * color;

    FragColor = vec4(result, 1.0);
}