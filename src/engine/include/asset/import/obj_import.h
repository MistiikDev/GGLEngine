#ifndef OBJIMPORTER_H
#define OBJIMPORTER_H


#define OBJ_EXTENSION ".obj"
#define MTL_EXTENSION ".mtl"

#define OBJ_DELIM '/'

#define ERR_MODEL "ERROR LOADING MODEL"
#define ERR_MAT "ERROR LOADING MTL"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

#include <global/globals.h>
#include <render/mesh.h>
#include <render/vertex.h>

struct Face {

    int vPos;
    int vTex;
    int vNorm;

} ;

struct OBJ_Material {

    OBJ_Material() {
        name = "";
        
        specular_factor = 1.0f;

        ambiantColor = Vector3(1.0f, 0.0f, 0.0f);
        diffuseColor = Vector3(1.0f, 0.0f, 0.0f);
        specularColor = Vector3(1.0f, 0.0f, 0.0f);
        emissiveColor = Vector3(1.0f, 0.0f, 0.0f);
    }


    
    std::string name;

    std::string diffuse_tex;
    std::string specular_tex;
    std::string normal_tex;

    Vector3 ambiantColor;
    Vector3 diffuseColor;
    Vector3 specularColor;
    Vector3 emissiveColor;

    float specular_factor;

};

class OBJImport {
    public:
        static void _loadOBJ( const char* fileDirectory, Mesh_Data* obj_data, Material_Data* mtl_data );

    private:
        static void _readOBJ( const char* objName, Mesh_Data* obj_data, Material_Data* materials );
        static void _readMTL( const char* mtlName, Material_Data* materials );
};

#endif