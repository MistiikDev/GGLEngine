#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <global/maths/CFrame.h>
#include <render/OpenGL/GLShader.h>

class PointLight {
    public: 
        glm::vec3 lightColor;
        CFrame lightCFrame;

        PointLight();
        PointLight(glm::vec3 position);
        PointLight(glm::vec3 position, glm::vec3 color);

        void Render();
        void Destroy();
    private:
        GLShader m_lightShader;
};

#endif