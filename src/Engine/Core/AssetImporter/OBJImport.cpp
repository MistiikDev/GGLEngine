#include "OBJImport.h"

OBJ_Data OBJImport::_loadOBJ( const char* fileDirectory ) {
    OBJ_Data _obj_data;

    std::ifstream objFile(fileDirectory);

    if (!objFile.is_open())
    {
        std::cout << ERR_LOAD_MODEL;
        throw EXIT_FAILURE;
    }

    std::string currentLineBuffer;

    std::vector<Vector3> positions;
    std::vector<Vector3> normals;
    std::vector<Vector2> texUV;

    std::vector<Vertex> verticies;
    std::vector<uint16_t> indicies;

    std::unordered_map<Vertex, uint16_t, VertexHash> VertexToIndex;

    ///
    while (std::getline(objFile, currentLineBuffer))
    {
        std::stringstream tokenParser(currentLineBuffer);
        std::string keyword;

        tokenParser >> keyword;

        if (keyword == "v" || keyword == "vn")
        {
            float x, y, z;
            tokenParser >> x >> y >> z;

            (keyword == "v" ? positions : normals).emplace_back(x, y, z);
        }
        else if (keyword == "vt")
        {
            float u, v;
            tokenParser >> u >> v;

            texUV.emplace_back(u, v);
        }
        else if (keyword == "f")
        {
            std::string vertData;
            std::vector<std::string> vertexIndexData;
            std::vector<uint16_t> tempIndicies;

            while (tokenParser >> vertData)
            {
                vertexIndexData.clear();
                StringUtils::split(vertData, OBJ_FACE_DELIM, vertexIndexData);

                int posIdx = (vertexIndexData.size() > 0 && !vertexIndexData[0].empty()) ? std::stoi(vertexIndexData[0]) : 0;
                int texIdx = (vertexIndexData.size() > 1 && !vertexIndexData[1].empty()) ? std::stoi(vertexIndexData[1]) : 0;
                int normIdx = (vertexIndexData.size() > 2 && !vertexIndexData[2].empty()) ? std::stoi(vertexIndexData[2]) : 0;

                // OBJ indices are 1-based
                Vector3 vPos = (posIdx <= 0) ? Vector3(0, 0, 0) : positions[posIdx - 1];
                Vector2 vTexUV = (texIdx <= 0) ? Vector2(0, 0) : texUV[texIdx - 1];
                Vector3 vNorm = (normIdx <= 0) ? Vector3(0, 0, 0) : normals[normIdx - 1];

                Vertex v;
                v.Position = vPos;
                v.TexUV = vTexUV;
                v.Normal = vNorm;
                v.Color = Vector3(1.0f, 1.0f, 1.0f);

                verticies.push_back(v);

                if (VertexToIndex.count(v))
                {
                    tempIndicies.push_back(VertexToIndex[v]);
                }
                else
                {
                    VertexToIndex[v] = verticies.size() - 1;
                    tempIndicies.push_back(verticies.size() - 1);
                }
            }

            // Process the face data (triangulate if necessary)
            if (tempIndicies.size() > 3) {
                // Modifiy the temp indicies vector

                uint16_t pivotIndex = tempIndicies[0];

                for (int i = 1; i < tempIndicies.size() - 1; i++) {
                    uint16_t currentIndex = tempIndicies[i];
                    uint16_t neighbourIndex = tempIndicies[i + 1];

                    // Push back current triangle
                    indicies.push_back(pivotIndex);
                    indicies.push_back(currentIndex);
                    indicies.push_back(neighbourIndex);
                }
            } else {
                indicies.insert(indicies.end(), tempIndicies.begin(), tempIndicies.end());
            }
        }
    }

    _obj_data.vertices = verticies;
    _obj_data.indicies = indicies;

    return _obj_data;
}