#ifndef GGLENGINE_POINTLIGHT_H
#define GGLENGINE_POINTLIGHT_H

#include "CFrame.h"
#include "ShaderInstance.h"

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
        ShaderInstance m_lightShader;
};

#endif