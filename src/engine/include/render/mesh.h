#ifndef MESH_H
#define MESH_H

#pragma once

#define DEFAULT_VERT_SHADER "src/game/data/shaders/VShaders/default.vert"
#define DEFAULT_FRAG_SHADER "src/game/data/shaders/FShaders/default.frag"

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

class OBJ_Data;
class MTL_Data;

class Mesh {
    public:
        glm::vec3 position;

        std::vector<Vertex> verticies;
        std::vector<uint32_t> indicies;

        std::unordered_map<std::string, Material> material_hash;
        std::unordered_map<std::string, std::vector<UI32_Range>> material_range;

        Mesh( GLShader* shader, 
            OBJ_Data* obj_data,
            MTL_Data* mtl_data
        ); // Mesh from OBJ overload
        
        void Draw( Camera& currentCamera );
    private:
        GLArray m_modelVertexArray;
        GLBuf m_modelBuffer;
        GLBuf m_modelIndexBuffer;

        GLShader* m_shader;
};

#endif

