#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 textureCoordinates;
in vec3 normal;
in vec3 worldPosition;

uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 camera_position;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
};

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform Material material;

void main(  ) {
    float lightIntensity = 3.0;

    vec3 viewDir = normalize(camera_position - worldPosition);
    vec3 lightDir = normalize(vec3(-10, 10, 10) - worldPosition);

    vec3 reflectedDir = reflect(-lightDir, normal);

    float light_dir = max(dot(normal, normalize(vec3(-10, 10, 10) - worldPosition)), 0);
    float spec = pow(max(dot(viewDir, reflectedDir), 0), material.shininess * 10);

    vec3 diffuseTexRGB = texture(diffuseMap, textureCoordinates).rgb;
    vec3 specularTexRGB = texture(specularMap, textureCoordinates).rgb;

    vec3 ambient = material.ambient;
    vec3 specular = material.specular * spec * diffuseTexRGB; 
    vec3 diffuse = material.diffuse * light_dir * specularTexRGB;

    vec3 result = (diffuse + specular) * color * lightIntensity;

    FragColor = vec4(result, 1.0);
}