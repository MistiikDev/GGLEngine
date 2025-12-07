#ifndef GGLENGINE_ASSETIMPORT_H
#define GGLENGINE_ASSETIMPORT_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <vector>

#include "Vertex.h"

struct OBJ_FaceData {
    int PositionIndex;
    int UVIndex;
    int NormalIndex;
};

struct G_Model {
    std::vector<Vertex> verticies;
    std::vector<int> indicies;
};

class AssetImport {
    public:
        static G_Model _load_GMDL(const char* fileDirectory);
        static void _write_GMDL_fromOBJ(const char* objDirectory, const char* targetDir);

    private:
        static void logMessage(const char* log, bool m_skipNewLine);
};

#endif