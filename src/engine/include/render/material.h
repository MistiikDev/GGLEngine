#ifndef MATERIAL_H
#define MATERIAL_H

#include <global/globals.h>
#include <global/maths/Vector3.h>

using string = std::string;

typedef struct {
    string name;
    ui16 texture_id;

    Vector3 ambiantColor;
    Vector3 diffuseColor;
    Vector3 specularColor;
    Vector3 emissiveColor;

    float specular_factor;
} Material;

#endif
