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
void triangulate_poly(std::vector<ui32>& temp_indicies, std::vector<ui32>& target_indicies) {
    for (int i = 1; i < (int)temp_indicies.size() - 1; i++) {
        target_indicies.push_back(temp_indicies.at(0));
        target_indicies.push_back(temp_indicies.at(i));
        target_indicies.push_back(temp_indicies.at(i + 1));
    }
}

void OBJImport::_loadOBJ( const char* fileDirectory, Mesh_Data* obj_data, Material_Data* mtl_data ) {
    std::string objLocation = std::string(fileDirectory) + OBJ_EXTENSION;
    std::string mtlLocation = std::string(fileDirectory) + MTL_EXTENSION;

    OBJImport::_readMTL(mtlLocation.c_str(), mtl_data);
    OBJImport::_readOBJ(objLocation.c_str(), obj_data, mtl_data);
}

void OBJImport::_readOBJ(const char* objFile, Mesh_Data* obj_data, Material_Data* material_data) {
    std::vector<Vector3> positions;
    std::vector<Vector3> normals;
    std::vector<Vector2> texUV;

    // Verticies Registering
    std::vector<Vertex> verticies;
    std::vector<ui32> indicies;
    std::vector<ui32> temp_indicies;
    std::unordered_map<Vertex, ui32, VertexHash> vertex_to_index;


    std::vector<SubMesh_Data> sub_meshes;
    std::string currentMatName = "";

    uint32_t temp_start_index = 0;

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
                    vertex_to_index[v] = verticies.size();
                    verticies.push_back(v);
                }

                temp_indicies.push_back( vertex_to_index[v] );
            }

            triangulate_poly(temp_indicies, indicies);

        } else if (keyword == "usemtl") {
            std::string matName;
            ss >> matName;

            if (!currentMatName.empty()) {
                SubMesh_Data submesh = SubMesh_Data {};
                
                submesh.indexOffset = temp_start_index;
                submesh.indexCount = indicies.size() - temp_start_index;
                submesh.material = material_data->name_to_material[currentMatName];
            
                sub_meshes.push_back(submesh);
            }
            
            currentMatName = matName;
            temp_start_index = indicies.size();
        }
    });

    if (!currentMatName.empty()) {
        SubMesh_Data submesh = SubMesh_Data {};
                
        submesh.indexOffset = temp_start_index;
        submesh.indexCount = indicies.size() - temp_start_index;
        submesh.material = material_data->name_to_material[currentMatName];
            
        sub_meshes.push_back(submesh);
    }

    obj_data->vertices = verticies;
    obj_data->indicies = indicies;
    obj_data->sub_meshes = sub_meshes;

    Engine::log::print("[OBJ IMPORTER] ", "-> Imported ", verticies.size(), " verticies");
    Engine::log::print("[OBJ IMPORTER] ", "-> Registered ", indicies.size(), " indices");
    Engine::log::print("[OBJ IMPORTER] ", "-> Registered ", sub_meshes.size(), " submeshes");

}


void OBJImport::_readMTL( const char* mtlFile, Material_Data* _mtl_Data ) {
    std::unordered_map<std::string, OBJ_Material> OBJ_material_parse;
    std::unordered_map<std::string, Material*> name_to_material;

    OBJ_Material temp_material {};

    Engine::file::parse( mtlFile, ERR_MODEL, [&]( std::stringstream& ss, std::string& line ) {
        std::string keyword;
        ss >> keyword;

        if (keyword == "newmtl") {
            if (!temp_material.name.empty()) {
                OBJ_material_parse[temp_material.name] = temp_material;
            }

            std::string matName;
            ss >> matName;

            temp_material = OBJ_Material {};
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

            temp_material.diffuse_tex = diffuse_tex_loc;
        } else if (keyword == "map_Ks") {
            std::string specular_tex_loc;
            ss >> specular_tex_loc;

            temp_material.specular_tex = specular_tex_loc;
        }
    });
    
    if (!temp_material.name.empty()) {
        OBJ_material_parse[temp_material.name] = temp_material;
    }

    for (const auto& kv : OBJ_material_parse) {
        std::string material_name = kv.first;
        OBJ_Material obj_mat = kv.second;

        Material* mat = new Material();
        mat->specular_factor = obj_mat.specular_factor;
        mat->ambiantColor = obj_mat.ambiantColor;
        mat->diffuseColor = obj_mat.diffuseColor;
        mat->specularColor = obj_mat.specularColor;
        mat->emissiveColor = obj_mat.emissiveColor;

        if (!obj_mat.diffuse_tex.empty()) {
            std::cout << obj_mat.diffuse_tex << std::endl;
            std::shared_ptr<GLTex> diffuse_tex = std::make_shared<GLTex>( obj_mat.diffuse_tex.c_str() );

            mat->diffuseTex = std::move(diffuse_tex);
        }

        if (!obj_mat.specular_tex.empty()) {
            std::cout << obj_mat.specular_tex << std::endl;
            std::shared_ptr<GLTex> specular_tex = std::make_shared<GLTex>( obj_mat.specular_tex.c_str() );

            mat->specularTex = std::move(specular_tex);
        }

        name_to_material[material_name] = mat;
    }

    Engine::log::print("[OBJ IMPORTER] ", "-> Loaded ", OBJ_material_parse.size(), " materials");

    _mtl_Data->name_to_material = std::move(name_to_material);
}