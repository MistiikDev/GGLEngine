#ifndef INSTANCE_H
#define INSTANCE_H

#include <string>
#include <globals>

#include "CFrame.h"
#include "Vector3.h"

#include "mesh.h"

class Instance {
    public:
        std::string name;
        CFrame cframe;

        Instance(std::string& name, CFrame& cframe);
        Instance(std::string& name, Vector3 position);
    private:
        std::string uid;
        G_mesh mesh;
};

#endif