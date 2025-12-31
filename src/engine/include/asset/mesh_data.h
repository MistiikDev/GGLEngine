#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <iostream>
#include <memory>
#include <vector>

#include <bits/stdc++.h>
#include <render/vertex.h>
#include <render/material.h>

struct SubMesh_Data {
    uint32_t indexOffset;
    uint32_t indexCount;

    Material* material;
};

struct Mesh_Data {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indicies;

    std::vector<SubMesh_Data> sub_meshes;
};

#endif // MESH_DATA_H