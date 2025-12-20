#include <asset/import/obj_import.h>


void OBJImport::_loadOBJ( const char* fileDirectory, OBJ_Data* obj_data, MTL_Data* mtl_data ) {
    std::string objLocation = std::string(fileDirectory) + OBJ_EXTENSION;
    std::string mtlLocation = std::string(fileDirectory) + MTL_EXTENSION;

    OBJImport::_readMTL(mtlLocation.c_str(), mtl_data);
    OBJImport::_readOBJ(objLocation.c_str(), obj_data, mtl_data);
}

void OBJImport::_readOBJ(const char* objFile, OBJ_Data* obj_data, MTL_Data* material_data) {
    std::vector<Vector3> positions;
    std::vector<Vector3> normals;
    std::vector<Vector2> texUV;

    std::vector<Vertex> verticies;
    std::vector<uint32_t> indicies;

    std::vector<Vertex> temp_verticies;

    Engine::file::parse( objFile, ERR_MODEL, [&]( std::stringstream& ss, std::string& line ) {
        std::string keyword;
        ss >> keyword;

        Vector3 vec3;
        Vector2 vec2;

        std::vector<Vector3> face; // f x/y/z x/y/z x/y/z ...

        if (keyword == "v" || keyword == "vn") {
            ss >> vec3.x >> vec3.y >> vec3.z;

            keyword == "v" ? positions.emplace_back(vec3) : normals.emplace_back(vec3);
        } else if (keyword == "vt") {
            ss >> vec2.x >> vec2.y;

            texUV.emplace_back(vec2);
        } else if (keyword == "f") {
            temp_verticies.clear();
            std::string triplet;

            while (ss >> triplet) {
                int vp = 0, vt = 0, vn = 0;
                int iseparatorCount = std::count(triplet.begin(), triplet.end(), '/');

                if (triplet.find("//") != std::string::npos) {
                    sscanf(triplet.c_str(), "%d//%d", &vp, &vn);
                }
                
                else if (iseparatorCount == 1) {
                    sscanf(triplet.c_str(), "%d/%d", &vp, &vt);
                } 
                
                else if (iseparatorCount == 2) {
                    sscanf(triplet.c_str(), "%d/%d/%d", &vp, &vt, &vn);
                }
                
                face.emplace_back(vp, vt, vn);
            }

            for (Vector3& vertexData : face) {
                Vector3 vPos = (vertexData.x != 0 ? positions[vertexData.x - 1] : Vector3());
                Vector2 vTex = (vertexData.y != 0 ? texUV[vertexData.y - 1] : Vector2());
                Vector3 vNorm = (vertexData.z != 0 ? normals[vertexData.z - 1] : Vector3());

                Vertex v;
                v.Position = vPos;
                v.TexUV = vTex;
                v.Normal = vNorm;
                v.Color = Vector3(1.0f);

                temp_verticies.push_back(v);
            }

            if (temp_verticies.size() >= 3) {
                Vertex v0 = temp_verticies[0];

                for (int i = 1; i < (int)temp_verticies.size() - 1; i++) {
                    Vertex v_i = temp_verticies[i];
                    Vertex v_i_next = temp_verticies[i+1];

                    indicies.push_back(0);
                    indicies.push_back(i);
                    indicies.push_back(i + 1);

                    verticies.push_back(v0);
                    verticies.push_back(v_i);
                    verticies.push_back(v_i_next);
                }
            }
        }
    });
}


void OBJImport::_readMTL( const char* mtlFile, MTL_Data* _mtl_Data ) {
    
}