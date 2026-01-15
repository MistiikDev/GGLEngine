#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <global/globals.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <graphics.h>

struct Bootstrap {
    public:
        static bool Init() {
            GRAPHIC_INIT( RENDER_ENGINE::OPEN_GL );
        }

    private:
        Bootstrap() = delete;
        ~Bootstrap() = delete;
};

#endif