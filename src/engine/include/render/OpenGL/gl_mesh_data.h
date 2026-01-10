#ifndef GLMesh_DATA_H
#define GLMesh_DATA_H

#include <iostream>
#include <memory>
#include <vector>

#include <bits/stdc++.h>
#include <render/vertex.h>
#include <render/OpenGL/GLMaterial.h>

struct SubGLMesh_Data {
    uint32_t indexOffset;
    uint32_t indexCount;

    GLMaterial* GLMaterial;
};

struct GLMesh_Data {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indicies;

    std::vector<SubGLMesh_Data> sub_GLMeshes;
};

#endif // GLMesh_DATA_H