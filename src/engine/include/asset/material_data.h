#ifndef MATERIAL_DATA_H
#define MATERIAL_DATA_H

#include <iostream>
#include <memory>
#include <unordered_map>

#include <render/vertex.h>
#include <render/material.h>

struct Material_Data {
    std::unordered_map<std::string, Material*> name_to_material;
};

#endif // MATERIAL_DATA_H