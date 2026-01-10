#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <scene/components.h>
#include <Transform.h>

struct TRANSFORM : Component {
    public:
        Transform transform;

        void Tick(unsigned int deltaTime) override {

        }
    private:
};

#endif