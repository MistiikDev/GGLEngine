#ifndef INSTANCE_H
#define INSTANCE_H

#include <string>
#include <global/globals.h>

#include <global/maths/CFrame.h>
#include <global/maths/Vector3.h>

#include "mesh.h"

class Instance {
    public:
        std::string name;
        CFrame cframe;

        Instance( std::string& name, CFrame& cframe );
        Instance( std::string& name, Vector3 position );
    private:
        std::string uid;
};

#endif