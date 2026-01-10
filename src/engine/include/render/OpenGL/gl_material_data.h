#ifndef GLMaterial_DATA_H
#define GLMaterial_DATA_H

#include <iostream>
#include <memory>
#include <unordered_map>

#include <render/vertex.h>
#include <render/OpenGL/GLMaterial.h>

struct GLMaterial_Data {
    std::unordered_map<std::string, GLMaterial*> name_to_GLMaterial;
};

#endif // GLMaterial_DATA_H