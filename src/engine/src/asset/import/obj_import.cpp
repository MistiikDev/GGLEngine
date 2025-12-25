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

    // Verticies Registering
    std::vector<Vertex> verticies;
    std::vector<ui32> indicies;

    std::vector<Vertex> temp_verticies;
    std::vector<ui32> temp_indicies;

    std::unordered_map<Vertex, ui32, VertexHash> hash_vtoi;

    // Material Registering
    std::unordered_map<std::string, std::vector<UI32_Range>> hash_matToIndex;

    std::string temp_material_name;
    ui32 temp_start_index;

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
        } else if (keyword == "usemtl") {
            std::string matName;
            ss >> matName;

            if (!(temp_material_name.empty())) {
                UI32_Range range;
                range.start = temp_start_index;
                range.end = indicies.size();
                range.length = range.end - range.start;

                hash_matToIndex[temp_material_name].push_back(range);
            }

            temp_material_name = matName;
            temp_start_index = indicies.size();
        }
    });

    obj_data->vertices = verticies;
    obj_data->indicies = indicies;

    Engine::log::print("[OBJ IMPORTER] ", "-> Imported ", verticies.size(), " verticies");
    Engine::log::print("[OBJ IMPORTER] ", "-> Registered ", indicies.size(), " indices");

    material_data->matToRange = std::move(hash_matToIndex);
}


void OBJImport::_readMTL( const char* mtlFile, MTL_Data* _mtl_Data ) {
    std::unordered_map<std::string, Material> nameToMat;

    Material temp_material;
    temp_material.name = "";

    Engine::file::parse( mtlFile, ERR_MODEL, [&]( std::stringstream& ss, std::string& line ) {
        std::string keyword;
        ss >> keyword;

        if (keyword == "newmtl") {
            if (!temp_material.name.empty()) {
                nameToMat[temp_material.name] = temp_material;
                temp_material.name = "";
            }

            std::string matName;
            ss >> matName;

            temp_material = Material {};
            temp_material.name = matName;

        } else if (keyword == "Ns") {
            float specular;
            ss >> specular;

            temp_material.specular_factor = specular;
        } else if (keyword == "Ka") {
            float ax, ay, az;
            ss >> ax >> ay >> az;

            temp_material.ambiantColor = Vector3(ax, ay, az);
        } else if (keyword == "Kd") {
            float dx, dy, dz;
            ss >> dx >> dy >> dz;

            temp_material.diffuseColor = Vector3(dx, dy, dz);
        } else if (keyword == "Ks") {
            float sx, sy, sz;
            ss >> sx >> sy >> sz;

            temp_material.specularColor = Vector3(sx, sy, sz);
        } else if (keyword == "map_Kd") {
            std::string diffuse_tex_loc;
            ss >> diffuse_tex_loc;

            temp_material.diffuse_texture = diffuse_tex_loc;
        } else if (keyword == "map_Ks") {
            std::string specular_tex_loc;
            ss >> specular_tex_loc;

            temp_material.diffuse_texture = specular_tex_loc;
        }
    });

    Engine::log::print("[OBJ IMPORTER] ", "-> Registered ", nameToMat.size(), " materials");

    _mtl_Data->nameToMat = std::move(nameToMat);
}