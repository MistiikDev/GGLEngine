#ifndef GGLENGINE_ASSETIMPORT_H
#define GGLENGINE_ASSETIMPORT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

#include <string>
#include <map>
#include <vector>

#include "Vertex.h"
#include "OBJImport.h"
#include "StringUtils.h"

#pragma once


struct G_Mesh {
    std::vector<Vertex> verticies;
    std::vector<uint16_t> indicies;
};

class AssetImport {
    public:
        static G_Mesh _load_GMDL(const char* fileDirectory);
        static void _write_GMDL_fromOBJ(const char* objDirectory, const char* targetDir);

    private:
        static void logMessage(const char* log, bool m_skipNewLine);
};

#endif