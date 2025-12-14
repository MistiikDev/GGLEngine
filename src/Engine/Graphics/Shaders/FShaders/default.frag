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
    float lightIntensity = 3.0;

    vec3 viewDir = normalize(camera_position - worldPosition);
    vec3 lightDir = normalize(vec3(-10, 10.0, 10.0) - worldPosition);
    vec3 reflectedDir = reflect(-lightDir, normal);

    float light_dir = max(dot(normal, normalize(vec3(-10, 10.0, 10.0) - worldPosition)), 0);
    float spec = pow(max(dot(viewDir, reflectedDir), 0), material.shininess * 10);

    vec3 ambient_lighting = material.ambient * vec3(1.0f, 1.0f, 1.0f);
    vec3 specular = spec * material.specular * vec3(1.0f, 1.0f, 1.0f); 
    vec3 diffuse = light_dir * material.diffuse * vec3(1.0f, 1.0f, 1.0f);

    vec3 result = (ambient_lighting + diffuse + specular) * color * lightIntensity;

    FragColor = vec4(result, 1.0);
}