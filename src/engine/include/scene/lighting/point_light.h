#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <global/maths/CFrame.h>
#include <render/OpenGL/GLShader.h>

class PointLight {
    public: 
        Vector3 lightPosition;
        Vector3 lightColor;

        CFrame lightCFrame;

        PointLight();
        PointLight(Vector3 position);
        PointLight(Vector3 position, Vector3 color);

        void Render();
        void Destroy();
    private:
        GLShader m_lightShader;
};

#endif