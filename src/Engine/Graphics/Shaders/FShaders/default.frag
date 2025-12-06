#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 textureCoordinates;
in vec3 normal;
in vec3 worldPosition;

uniform sampler2D texture0;

uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 camera_position;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main(  ) {
    vec3 viewDir = normalize(light_position - camera_position);
    vec3 reflectedDir = reflect(viewDir, normal);

    float light_dir = max(dot(normal, normalize(light_position - worldPosition)), 0);
    float spec = pow(max(dot(viewDir, reflectedDir), 0), material.shininess);

    vec3 ambient_lighting = material.ambient * light_color;
    vec3 specular = spec * material.specular * light_color; 
    vec3 diffuse = light_dir * light_color;

    vec3 result = (ambient_lighting + diffuse + specular) * color;

    FragColor = vec4(result, 1.0);
}