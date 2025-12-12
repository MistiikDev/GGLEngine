#ifndef GGLENGINE_OBJIMPORTER_H
#define GGLENGINE_OBJIMPORTER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

#include <string>
#include <vector>

#include "Vertex.h"
#include "StringUtils.h"
#include "Log.h"

const inline char OBJ_FACE_DELIM = '/';

const inline char* ERR_LOAD_MODEL = "ERROR LOADING MODEL";
const inline char* ERR_WRITE_MODEL = "ERROR WRITING MODEL";
const inline char* ERR_LOAD_GMDL = "ERROR LOADING GMDL BINARY";

struct OBJ_Data {
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indicies;
};

class OBJImport {
    public:
        static OBJ_Data _loadOBJ(const char* fileDirectory);
};

#endif