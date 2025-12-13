#ifndef GGLENGINE_MESH_H
#define GGLENGINE_MESH_H

#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Vector3.h"
#include "Vertex.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include "ShaderInstance.h"
#include "Camera.h"

struct MeshMaterial {
    float specular_factor;

    Vector3 ambiantColor;
    Vector3 diffuseColor;
    Vector3 specularColor;
    Vector3 emissiveColor;

    const char* matName;
};

class Mesh {
    public:
        glm::vec3 position;
        std::vector<Vertex> verticies;
        std::vector<uint16_t> indicies;

        Mesh(std::vector<Vertex> in_verticies, std::vector<uint16_t> in_indicies);

        void Draw(Camera& currentCamera);
    private:
        VAO m_modelVertexArray;
        VBO m_modelBuffer;
        EBO m_modelIndexBuffer;

        ShaderInstance m_shader;
};

#endif