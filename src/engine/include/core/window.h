#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <global/globals.h>

#include <iostream>

class G_renderer;
class G_window {
    public: 
        unsigned int ScreenWidth;
        unsigned int ScreenHeight;

        G_window( const char* WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight );
        
        GLFWwindow* GetGLFWWindow();
        
        void Render();
        void Destroy();
    private:
        G_renderer* m_windowRenderer;
        GLFWwindow* m_glfwWindow;
};

#endif