#include <asset/import/obj_import.h>

void __read_vertex(std::vector<Face>& faces, std::string& triplet) { // triplet : vp/vt/vn
    int vp = 0, vt = 0, vn = 0;
    int iseparatorCount = std::count(triplet.begin(), triplet.end(), '/');

    if (triplet.find("//") != std::string::npos)
    {
        sscanf(triplet.c_str(), "%d//%d", &vp, &vn);
    }

    else if (iseparatorCount == 1)
    {
        sscanf(triplet.c_str(), "%d/%d", &vp, &vt);
    }

    else if (iseparatorCount == 2)
    {
        sscanf(triplet.c_str(), "%d/%d/%d", &vp, &vt, &vn);
    }

    Face f = {};
    f.vPos = vp;
    f.vTex = vt;
    f.vNorm = vn;

    faces.push_back(f);
}

// Triangulates indicies from temp to target
void __triangulate_indicies(std::vector<ui32>& temp_indicies, std::vector<ui32>& target_indicies) {
    for (int i = 1; i < (int)temp_indicies.size() - 1; i++) {
        target_indicies.push_back(temp_indicies.at(0));
        target_indicies.push_back(temp_indicies.at(i));
        target_indicies.push_back(temp_indicies.at(i + 1));
    }
}

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
    std::vector<ui32> indicies;

    std::vector<Vertex> temp_verticies;
    std::vector<ui32> temp_indicies;

    std::unordered_map<Vertex, ui32, VertexHash> hash_vtoi;

    Engine::file::parse( objFile, ERR_MODEL, [&]( std::stringstream& ss, std::string& line ) {
        std::string keyword;
        ss >> keyword;

        Vector3 vec3;
        Vector2 vec2;

        std::vector<Face> faces;

        if (keyword == "v" || keyword == "vn") {
            ss >> vec3.x >> vec3.y >> vec3.z;

            keyword == "v" ? positions.emplace_back(vec3) : normals.emplace_back(vec3);
        } else if (keyword == "vt") {
            ss >> vec2.x >> vec2.y;

            texUV.emplace_back(vec2);
        } else if (keyword == "f") {
            temp_verticies.clear();
            temp_indicies.clear();
            faces.clear();

            std::string triplet;

            while (ss >> triplet) {
                __read_vertex(faces, triplet); // Reads triplet data into faces as readable integers
            }

            for (Face& vertexData : faces) {
                Vector3 vPos = (vertexData.vPos != 0 ? positions.at(vertexData.vPos - 1) : Vector3(0.0f));
                Vector2 vTex = (vertexData.vTex != 0 ? texUV.at(vertexData.vTex - 1) : Vector2(0.0f));
                Vector3 vNorm = (vertexData.vNorm != 0 ? normals.at(vertexData.vNorm - 1) : Vector3(0.0f));

                Vertex v;
                v.Position = vPos;
                v.TexUV = vTex;
                v.Normal = vNorm;
                v.Color = Vector3(1.0f);

                if ( std::find( verticies.begin(), verticies.end(), v ) == verticies.end() ) {
                    hash_vtoi[v] = verticies.size();
                    verticies.push_back(v);
                }

                temp_indicies.push_back( hash_vtoi[v] );
            }

            __triangulate_indicies(temp_indicies, indicies);
        }
    });

    obj_data->vertices = verticies;
    obj_data->indicies = indicies;
}


void OBJImport::_readMTL( const char* mtlFile, MTL_Data* _mtl_Data ) {
    
}