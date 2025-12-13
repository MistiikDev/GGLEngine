#ifndef GGLENGINE_WINDOW_H
#define GGLENGINE_WINDOW_H

#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class Renderer;
class Window {
    public: 
        unsigned int ScreenWidth;
        unsigned int ScreenHeight;

        Window(const char* WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight);
        
        GLFWwindow* GetGLFWWindow();
        
        void Render();
        void Destroy();
    private:
        Renderer* m_windowRenderer;
        GLFWwindow* m_glfwWindow;
};

#endif