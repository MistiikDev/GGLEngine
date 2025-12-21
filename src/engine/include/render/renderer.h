#ifndef RENDERER_H
#define RENDERER_H

#include <stb/stb_image.h>
#include <iostream>
#include <memory>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <asset/import/obj_import.h>
#include <core/camera.h>
#include <render/mesh.h>
#include <scene/lighting/point_light.h>
#include <global/globals.h>

class G_window;
class G_renderer {
    public: 
        PointLight m_sceneLight;
        Camera m_currentCamera;
        
        G_renderer( G_window* m_window, unsigned int ScreenWidth, unsigned int ScreenHeight );

        void Render();
        void Destroy();
    private:
        G_window* m_window;
        Mesh* m_mesh;
};

#endif