#ifndef GLMesh_H
#define GLMesh_H

#pragma once

#include <asset/default_assets.h>

#include <core/camera.h>
#include <render/vertex.h>
#include <render/mesh.h>
#include <render/material.h>

#include <render/OpenGL/GLArray.h>
#include <render/OpenGL/GLBuf.h>
#include <render/OpenGL/GLShader.h>

#include <render/OpenGL/gl_mesh_data.h>
#include <render/OpenGL/gl_material_data.h>

#include <global/globals.h>
#include <global/maths/Transform.h>

class GLMesh : public Mesh {
    public:
        GLMesh_Data GLMesh_data;
        GLMaterial_Data GLMaterial_data;
        
        Transform transform;

        GLMesh(  GLMesh_Data& GLMesh_data, GLMaterial_Data& GLMaterial_data );
    private:
        GLArray m_modelVertexArray;
        GLBuf m_modelBuffer;
        GLBuf m_modelIndexBuffer;
};

#endif

