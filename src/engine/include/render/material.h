#ifndef MATERIAL_H
#define MATERIAL_H

#include <global/globals.h>
#include <global/maths/Vector3.h>

using string = std::string;

typedef struct {
    string name;

    string diffuse_texture;
    string specular_texture;
    string ambiant_texture;
    string alpha_texture;

    string normal_texture;

    GLuint texture_id;
    GLuint index_offset;

    Vector3 ambiantColor;
    Vector3 diffuseColor;
    Vector3 specularColor;
    Vector3 emissiveColor;

    float specular_factor;
} Material;

#endif
