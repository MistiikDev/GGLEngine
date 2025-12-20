#ifndef OBJIMPORTER_H
#define OBJIMPORTER_H


#define OBJ_EXTENSION ".obj"
#define MTL_EXTENSION ".mtl"

#define OBJ_DELIM '/'

#define ERR_MODEL "ERROR LOADING MODEL"
#define ERR_MAT "ERROR LOADING MTL"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

#include <global/globals.h>
#include <render/mesh.h>
#include <render/vertex.h>

struct OBJ_Data {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indicies;
};

struct MTL_Data {
    std::vector<Material> materials;
};

class OBJImport {
    public:
        static void _loadOBJ(const char* fileDirectory, OBJ_Data* obj_data, MTL_Data* mtl_data);

    private:
        static void _readOBJ(const char* objName, OBJ_Data* obj_data, MTL_Data* materials);
        static void _readMTL(const char* mtlName, MTL_Data* materials);
};

#endif