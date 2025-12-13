#ifndef GGLENGINE_RENDERER_H
#define GGLENGINE_RENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>
#include <iostream>
#include <memory>

#include "Camera.h"
#include "PointLight.h"
#include "Mesh.h"
#include "OBJImport.h"

class Window;
class Renderer {
    public: 
        bool b_isRendering;

        Renderer(Window* window, unsigned int ScreenWidth, unsigned int ScreenHeight);

        PointLight m_sceneLight;
        Camera m_currentCamera;

        void Render();
        void Destroy();
    private:
        Window* m_window;
        std::unique_ptr<Mesh> m_mesh;
};

#endif