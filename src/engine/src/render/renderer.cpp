#include <render/renderer.h>
#include <core/window.h>

#define CAMERA_FOV_DEGREES 45.0f
#define CAMERA_NEAR_Z 0.1f
#define CAMERA_FAR_Z 100.0f

G_renderer::G_renderer( G_window* window, unsigned int ScreenWidth, unsigned int ScreenHeight )
    : m_sceneLight( Vector3(-10.0, 10.0, 10.0) ), // crash here
      m_currentCamera( ScreenWidth, ScreenHeight, camera_origin ),
      m_window( window )
{
    
    // Init shader
    DefaultAssets::Init();
    TextureCache::Init();

    SetActiveShader(DefaultAssets::default_shader);

    GLMesh_Data GLMesh_data;
    GLMaterial_Data mtl_data;
    
    GLMesh_Data second_GLMesh_data;
    GLMaterial_Data second_mtl_data;

    OBJImport::_loadOBJ( "src/game/src/data/models/Cop", &GLMesh_data, &mtl_data );
    OBJImport::_loadOBJ( "src/game/src/data/models/Yoshi", &second_GLMesh_data, &second_mtl_data );

    m_GLMesh = new GLMesh(
        m_shader,
        GLMesh_data,
        mtl_data
    );

    m_GLMesh_second = new GLMesh(
        m_shader,
        second_GLMesh_data,
        second_mtl_data
    );
}



void G_renderer::SetActiveShader( GLShader* glshader ) {
    if (glshader == nullptr) {
        Engine::log::print("[RENDERER] : ",  "TRIED SETTING ACTIVE SHADER AS NULLPTR");

        return;
    }
    
    Engine::log::print("[RENDERER] : ", "-> Set Active Shader (", glshader, ")");

    this->m_shader = glshader;
}

void G_renderer::Render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glClearColor( 0.52f, 0.80f, 0.92f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_currentCamera.ComputeMatrix( CAMERA_NEAR_Z, CAMERA_FAR_Z, CAMERA_FOV_DEGREES );
    m_currentCamera.Input( m_window );

    static float scale = 1.0f;
    static float position[3] = {0.0f, 1.0f, 1.0f};

    m_sceneLight.Render();
    m_GLMesh->Draw( m_currentCamera );
    m_GLMesh_second->Draw( m_currentCamera );

    m_GLMesh->transform.Scale = glm::vec3(scale);
    m_GLMesh->transform.Position = glm::vec3(position[0], position[1], position[2]);

    // UI Handling

    ImGui::Begin("Debug");
    ImGui::Text("%.3f ms / %.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::SliderFloat("GLMesh Scale", &scale, 0.0f, 10.0f);
    ImGui::InputFloat3("GLMesh Position", position);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //

    glfwSwapBuffers( m_window->GetGLFWWindow() );
    glfwPollEvents();
}

void G_renderer::Destroy() {
    m_sceneLight.Destroy();
}