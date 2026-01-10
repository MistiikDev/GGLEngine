#ifndef RIGIDBODY_COMPONENT_H
#define RIGIDBODY_COMPONENT_H

#include <scene/components.h>

struct RIGIDBODY : Component {
    public:
        unsigned int gravityInfluence;
        
        bool b_isAnchored;
        bool b_CanCollide;
        bool b_CanArchive;

        void Tick(unsigned int deltaTime) override {
            
        };
    private:
        unsigned int bounding_x;
        unsigned int bounding_y;
};

#endif