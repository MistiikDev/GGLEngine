#version 330 core
layout (location = 0) in vec3 localPosition; // Object space position
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 color;
out vec2 texCoords;
out vec3 normal;
out vec3 worldPosition;

uniform mat4 vertexTransform;
uniform mat4 camera_matrix;

void main() {
    worldPosition = vec3(vertexTransform * vec4(localPosition, 1)); // world coords = matrix_transform * local coords
    gl_Position = camera_matrix * vec4(worldPosition, 1.0); // Position relative to camera

    color = aColor;
    texCoords = aTex;
    normal = aNormal;
}