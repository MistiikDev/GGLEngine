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
#include <asset/default_assets.h>

#include <core/camera.h>

#include <render/mesh.h>
#include <render/material.h>

#include <scene/lighting/point_light.h>
#include <global/globals.h>

const inline glm::vec3 camera_origin = glm::vec3(0.0f, 0.0f, 2.0f);

class G_window;
class G_renderer {
    public: 
        PointLight m_sceneLight;
        Camera m_currentCamera;
        
        G_renderer( G_window* m_window, unsigned int ScreenWidth, unsigned int ScreenHeight );

        void SetActiveShader( GLShader* glshader );

        void Render();
        void Destroy();
    private:
        G_window* m_window;
        GLShader* m_shader;
        
        Mesh* m_mesh;
};

#endif