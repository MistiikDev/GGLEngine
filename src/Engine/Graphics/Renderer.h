#ifndef GGLENGINE_RENDERER_H
#define GGLENGINE_RENDERER_H

#include <glad/glad.h>    
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>
#include <iostream>

#include "ShaderInstance.h"
#include "Texture.h"
#include "Camera.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.H"

class Window;
class Renderer {
    public: 
        bool b_isRendering;

        Renderer(Window* window, unsigned int ScreenWidth, unsigned int ScreenHeight);
        
        VAO vertexArray;
        VBO vertexBuffer;
        EBO indexBuffer;

        Texture texture0;
        
        ShaderInstance m_shaderInstance;
        Camera m_currentCamera;

        void Render();
        void Destroy();
    private:
        Window* m_window;

        VAO m_lightVAO;
        VBO m_lightVBO;
        EBO m_lightIndexBuffer;
        ShaderInstance m_lightShader;
};

#endif