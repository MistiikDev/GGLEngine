#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <scene/entities/entity.h>

struct Component {
    public:
        virtual void Start();
        virtual void Tick(unsigned int deltaTime);
        virtual void End();
    protected:
        Entity* m_pEntity;
};

#endif