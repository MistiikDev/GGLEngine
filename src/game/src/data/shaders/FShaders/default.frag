#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 textureCoordinates;
in vec3 normal;
in vec3 worldPosition;

uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 camera_position;

struct GLMaterial {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shininess;
};

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform GLMaterial GLMaterial;

void main( ) {
    float lightIntensity = 3.0;

    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(camera_position - worldPosition);
    vec3 lightDir = normalize(light_position - worldPosition);

    float diffuseFactor = 0.5; //max(dot(norm, lightDir), 0.0); // lightDir is not proprely transcribed 
    // tired will fucking fix fucking later 
    
    vec3 reflectDir = reflect(-lightDir, norm);
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), GLMaterial.shininess * 10.0);

    vec3 diffuseTexRGB = texture(diffuseMap, textureCoordinates).rgb;
    vec3 specularTexRGB = texture(specularMap, textureCoordinates).rgb;

    vec3 ambientComponent = GLMaterial.ambient;
    vec3 diffuseComponent = GLMaterial.diffuse * diffuseFactor * diffuseTexRGB;
    vec3 specularComponent = GLMaterial.specular * specularFactor * specularTexRGB;

    vec3 result = (diffuseComponent + specularComponent) * lightIntensity * color;

    FragColor = vec4(result, 1.0);
}