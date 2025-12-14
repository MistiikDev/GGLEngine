#ifndef GGLENGINE_OBJIMPORTER_H
#define GGLENGINE_OBJIMPORTER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

#include <string>
#include <vector>

#include "Mesh.h"
#include "Vertex.h"
#include "StringUtils.h"
#include "Log.h"

#define OBJ_EXTENSION ".obj"
#define MTL_EXTENSION ".mtl"

const inline char OBJ_FACE_DELIM = '/';

const inline char* WARN_NO_MTL = "WARNING: MATERIALS DEPS NOT FOUND IN DIRECTORY";

const inline char* ERR_LOAD_MODEL = "ERROR LOADING MODEL";
const inline char* ERR_WRITE_MODEL = "ERROR WRITING MODEL";
const inline char* ERR_LOAD_GMDL = "ERROR LOADING GMDL BINARY";

struct OBJ_Data {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indicies;

    std::vector<SubMesh> sub_meshes;
};

struct MTL_Data {
    std::vector<Material> materials;
};

struct OBJ {
    OBJ_Data geometryData;
    MTL_Data materials;
};

class OBJImport {
    public:
        static OBJ _loadOBJ(const char* fileDirectory);

    private:
        static OBJ_Data _readOBJ(const char* objName, MTL_Data& materials);
        static MTL_Data _readMTL(const char* mtlName);
};

#endif