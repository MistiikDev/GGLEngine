#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <unordered_map>
#include "mesh.h"

class G_scene {
    public:
        std::unordered_map<std::string&, Instance> v_nameToInstance;
};

#endif

