#include "OBJImport.h"

OBJ OBJImport::_loadOBJ( const char* fileDirectory ) {
    OBJ _obj;

    std::string objLocation = std::string(fileDirectory) + OBJ_EXTENSION;
    std::string mtlLocation = std::string(fileDirectory) + MTL_EXTENSION;

    MTL_Data _mtl_data = OBJImport::_readMTL(mtlLocation.c_str());
    OBJ_Data _obj_data = OBJImport::_readOBJ(objLocation.c_str());

    _obj.geometryData = _obj_data;
    _obj.materials = _mtl_data;

    return _obj;
}

OBJ_Data OBJImport::_readOBJ(const char* objFile) {
    OBJ_Data _obj_data;

    std::ifstream objStream(objFile);

    if (!objStream.is_open())
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
    std::unordered_map<Vertex, std::string, VertexHash> VertexToMaterial;

    std::string currentMaterial;

    ///
    while (std::getline(objStream, currentLineBuffer))
    {
        std::stringstream tokenParser(currentLineBuffer);
        std::string keyword;

        tokenParser >> keyword;

        if (keyword == "usemtl") {
            std::string materialName;
            tokenParser >> materialName;

            currentMaterial = materialName;
        } 
        else if (keyword == "v" || keyword == "vn")
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

                if (VertexToIndex.count(v))
                {
                    tempIndicies.push_back(VertexToIndex[v]);
                }
                else
                {
                    if (!currentMaterial.empty() && !VertexToMaterial.count(v) ) {
                        VertexToMaterial[v] = currentMaterial;
                    }

                    verticies.push_back(v);
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

    std::cout << "[OBJ IMPORT] Successfully loaded : "
          << verticies.size()
          << " vertices ("
          << indicies.size()
          << " indices).\n";

    _obj_data.vertices = verticies;
    _obj_data.indicies = indicies;
    _obj_data.VertexToMaterial = VertexToMaterial;

    return _obj_data;
}


MTL_Data OBJImport::_readMTL( const char* mtlFile ) {
    MTL_Data _mtl_Data;

    std::ifstream mtlStream(mtlFile);

    if (!mtlStream.good()) {
        std::cout << WARN_NO_MTL;

        return _mtl_Data;
    } else if (!mtlStream.is_open())
    {
        std::cout << ERR_LOAD_MODEL;
        throw EXIT_FAILURE;
    }

    std::string currentLineBuffer;
    std::vector<MTL_Material> materials;

    MTL_Material currentMaterial;

    while (std::getline(mtlStream, currentLineBuffer)) {
        std::stringstream tokenParser(currentLineBuffer);
        std::string keyword;

        tokenParser >> keyword;

        if (keyword == "newmtl") {
            if (currentMaterial.matName != nullptr) {
                // If there is a material already, add it to the list then reset its data
                materials.push_back(currentMaterial); 
            }

            std::string materialName;
            tokenParser >> materialName;

            currentMaterial = MTL_Material {};
            currentMaterial.matName = materialName.c_str();

        } else if (keyword == "Ns") {
            float specular_factor;
            tokenParser >> specular_factor;

            currentMaterial.specular_factor = specular_factor;
        } else if (keyword == "Ka") {
            float ax, ay, az;

            tokenParser >> ax >> ay >> az;
            currentMaterial.ambiantColor = Vector3(ax, ay, az);
        } else if (keyword == "Kd") {
            float dx, dy, dz;

            tokenParser >> dx >> dy >> dz;
            currentMaterial.diffuseColor = Vector3(dx, dy, dz);
        } else if (keyword == "Ks") {
            float sx, sy, sz;

            tokenParser >> sx >> sy >> sz;
            currentMaterial.specularColor = Vector3(sx, sy, sz);
        }
    }

    std::cout << "[OBJ IMPORT] Successfully loaded : " << materials.size() << " materials.\n";

    return _mtl_Data;
}