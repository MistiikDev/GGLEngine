#ifndef MESH_H
#define MESH_H

#include <core/camera.h>
#include <global/maths/Transform.h>

class Mesh {
    public: 
        Mesh( ) = default;

        virtual void EditVerticies();
        virtual void Draw( const Camera* current_camera );
        virtual void Destroy();
}

#endif