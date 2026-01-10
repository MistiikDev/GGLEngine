#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <global/maths/Transform.h>
#include <render/OpenGL/GLShader.h>

class PointLight {
    public: 
        Vector3 lightPosition;
        Vector3 lightColor;

        Transform lightTransform;

        PointLight( );
        PointLight( Vector3 position );
        PointLight( Vector3 position, Vector3 color );

        void Render();
        void Destroy();
    private:
        GLShader m_lightShader;
};

#endif