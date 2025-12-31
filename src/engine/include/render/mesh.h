#ifndef MESH_H
#define MESH_H

#pragma once

#include <asset/mesh_data.h>
#include <asset/material_data.h>
#include <asset/default_assets.h>

#include <core/camera.h>

#include <render/vertex.h>
#include <render/material.h>

#include <render/OpenGL/GLArray.h>
#include <render/OpenGL/GLBuf.h>
#include <render/OpenGL/GLShader.h>

#include <global/globals.h>
#include <global/maths/CFrame.h>

class Mesh {
    public:
        Mesh_Data mesh_data;
        Material_Data material_data;
        
        CFrame cframe;

        Mesh( GLShader* shader, Mesh_Data& mesh_data, Material_Data& material_data );
        
        void Draw( Camera& currentCamera );
    private:
        GLArray m_modelVertexArray;
        GLBuf m_modelBuffer;
        GLBuf m_modelIndexBuffer;

        GLShader* m_shader;
};

#endif

