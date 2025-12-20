#ifndef MESH_H
#define MESH_H

#define DEFAULT_VERT_SHADER "src/Engine/Graphics/Shaders/VShaders/default.vert"
#define DEFAULT_FRAG_SHADER "src/Engine/Graphics/Shaders/FShaders/default.frag"

#include <map>
#include <unordered_map>
#include <vector>

#include <core/camera.h>

#include <render/vertex.h>
#include <render/material.h>

#include <render/OpenGL/GLArray.h>
#include <render/OpenGL/GLBuf.h>
#include <render/OpenGL/GLShader.h>

#include <global/globals.h>

class Mesh {
    public:
        glm::vec3 position;

        std::vector<Vertex> verticies;
        std::vector<uint32_t> indicies;
        std::vector<Material> materials;

        std::unordered_map< std::string, Material > name_to_mat;

        Mesh( GLShader* shader, 
            std::vector<Vertex>& in_verticies, 
            std::vector<ui32>& in_indicies, 
            std::vector<Material>& meshMaterials 
        );
        
        void Draw( Camera& currentCamera );
    private:
        GLArray m_modelVertexArray;
        GLBuf m_modelBuffer;
        GLBuf m_modelIndexBuffer;

        GLShader* m_shader;
};
#endif

