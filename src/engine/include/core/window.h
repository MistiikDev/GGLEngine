#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <global/globals.h>

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

enum MouseState {
    MOUSE_FREE = 0b00,
    MOUSE_FOCUS = 0b01
};

class G_renderer;
class G_window {
    public: 
        unsigned int ScreenWidth;
        unsigned int ScreenHeight;

        G_window( const char* WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight );
        
        GLFWwindow* GetGLFWWindow();
        
        const MouseState GetMouseState() const { return m_mouseState; };

        void Render();
        void Input();
        void Destroy();
    private:
        MouseState m_mouseState;
        G_renderer* m_windowRenderer;
        GLFWwindow* m_glfwWindow;
};

#endif