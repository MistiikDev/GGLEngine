#ifndef GGLENGINE_MESH_H
#define GGLENGINE_MESH_H

#include <map>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Vector3.h"
#include "Vertex.h"
#include "GLArray.h"
#include "GLBuf.h"

#include "ShaderInstance.h"
#include "Camera.h"


struct SubMesh {
    size_t indiciesCount;
    size_t indiciesOffset; // Offset relating to parent mesh (4 if fifth index = fifth vertex....)

    std::string materialName;
};


struct Material {
    float specular_factor;

    std::string materialName;

    Vector3 ambiantColor;
    Vector3 diffuseColor;
    Vector3 specularColor;
    Vector3 emissiveColor;

    bool operator==( const Material& rhs ) const {
        return ambiantColor == rhs.ambiantColor && diffuseColor == rhs.diffuseColor && specularColor == rhs.specularColor && specularColor == rhs.emissiveColor && materialName == rhs.materialName;
    }
};

class Mesh {
    public:
        glm::vec3 position;

        std::vector<Vertex> verticies;
        std::vector<uint32_t> indicies;
        std::vector<SubMesh> sub_meshes;
        std::vector<Material> materials;

        Mesh(std::vector<Vertex>&& in_verticies, std::vector<uint32_t>&& in_indicies, std::vector<SubMesh>&& in_submeshes, std::vector<Material>&& meshMaterials);

        std::unordered_map<std::string, Material> name_to_mat;

        void Draw(Camera& currentCamera);
    private:
        GLArray m_modelVertexArray;
        GLBuf m_modelBuffer;
        GLBuf m_modelIndexBuffer;

        ShaderInstance m_shader;
};
#endif

