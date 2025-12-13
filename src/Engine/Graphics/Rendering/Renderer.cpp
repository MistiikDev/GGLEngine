#include "Renderer.h"
#include "Window.h"

#define CAMERA_FOV_DEGREES 45.0f
#define CAMERA_NEAR_Z 0.1f
#define CAMERA_FAR_Z 100.0f

const glm::vec3 camera_origin = glm::vec3(0.0f, 0.0f, 2.0f);

Renderer::Renderer(Window* window, unsigned int ScreenWidth, unsigned int ScreenHeight)
    : m_sceneLight(glm::vec3(0.5f)),
      m_currentCamera(ScreenWidth, ScreenHeight, camera_origin),
      m_window(window)
{
    OBJ testOBJ = OBJImport::_loadOBJ("src/Game/Models/Cop");

    m_mesh = std::make_unique<Mesh>(
        testOBJ.geometryData.vertices,
        testOBJ.geometryData.indicies
    );
}

void Renderer::Render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_currentCamera.ComputeMatrix(CAMERA_NEAR_Z, CAMERA_FAR_Z, CAMERA_FOV_DEGREES);
    m_currentCamera.Input(m_window->GetGLFWWindow());

    m_mesh->Draw(m_currentCamera);

    // 

    m_sceneLight.Render();
    //

    glfwSwapBuffers(m_window->GetGLFWWindow());
    glfwPollEvents();
}

void Renderer::Destroy() {
    m_sceneLight.Destroy();
}