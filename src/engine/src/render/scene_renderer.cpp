#include <render/scene_renderer.h>
#include <core/scene_window.h>

#define CAMERA_FOV_DEGREES 45.0f
#define CAMERA_NEAR_Z 0.1f
#define CAMERA_FAR_Z 100.0f

SceneRenderer::SceneRenderer( EditorViewport* window, unsigned int ScreenWidth, unsigned int ScreenHeight )
    : m_sceneLight( Vector3(-10.0, 10.0, 10.0) ), // crash here
      m_currentCamera( ScreenWidth, ScreenHeight, glm::vec3(0.0f, 0.0f, 2.0f) ),
      m_viewport( window )
{
    
    SetActiveShader(DefaultAssets::default_shader);

    GLMesh_Data GLMesh_data;
    GLMaterial_Data mtl_data;
    
    GLMesh_Data second_GLMesh_data;
    GLMaterial_Data second_mtl_data;

    OBJImport::_loadOBJ( "src/game/src/data/models/Cop", &GLMesh_data, &mtl_data );
    OBJImport::_loadOBJ( "src/game/src/data/models/Yoshi", &second_GLMesh_data, &second_mtl_data );
}

void SceneRenderer::SetActiveShader( GLShader* glshader ) {
    if (glshader == nullptr) {
        Engine::log::print("[RENDERER] : ",  "TRIED SETTING ACTIVE SHADER AS NULLPTR");

        return;
    }
    
    Engine::log::print("[RENDERER] : ", "-> Set Active Shader (", glshader, ")");

    this->m_shader = glshader;
}

void SceneRenderer::Render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glClearColor( 0.52f, 0.80f, 0.92f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_currentCamera.ComputeMatrix( CAMERA_NEAR_Z, CAMERA_FAR_Z, CAMERA_FOV_DEGREES );
    m_currentCamera.Input( m_viewport );

    m_sceneLight.Render();

    glfwSwapBuffers( m_viewport->GetGLFWWindow() );
    glfwPollEvents();
}

void SceneRenderer::Destroy() {
    m_sceneLight.Destroy();
}