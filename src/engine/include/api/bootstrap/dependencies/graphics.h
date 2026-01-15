#ifndef GRAPHICS_API
#define GRAPHICS_API

#pragma once

#include <asset/default_assets.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

enum RENDER_ENGINE {
    OPEN_GL,
    VULKAN,
    DIRECTX
};

static RENDER_ENGINE RenderingMode;

static void GRAPHIC_INIT(RENDER_ENGINE rendering_mode) {
    RenderingMode = rendering_mode;

    if (!glfwInit()) {
        Engine::log::print("[GLFW ERROR] : ", "FAILED INIT");
        return;
    }

    glfwSetErrorCallback(Engine::glfw::glfw_error_callback);

    if ( RenderingMode == RENDER_ENGINE::OPEN_GL ) {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            Engine::log::print("[GLAD ERROR] : ", "FAILURE");

            glfwTerminate();
            return;
        }

        Engine::log::print("[OPENGL] : ", glGetString(GL_VERSION));

        gladLoadGL();
        glEnable(GL_DEPTH_TEST);
    }

    //

    DefaultAssets::Init();
    TextureCache::Init();
}

#endif