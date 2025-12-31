#include <render/renderer.h>
#include <core/window.h>

#define DEFAULT_VERT_SHADER "src/game/data/shaders/VShaders/default.vert"
#define DEFAULT_FRAG_SHADER "src/game/data/shaders/FShaders/default.frag"

#define CAMERA_FOV_DEGREES 45.0f
#define CAMERA_NEAR_Z 0.1f
#define CAMERA_FAR_Z 100.0f

G_renderer::G_renderer( G_window* window, unsigned int ScreenWidth, unsigned int ScreenHeight )
    : m_sceneLight( Vector3(-10.0, 10.0, 10.0) ),
      m_currentCamera( ScreenWidth, ScreenHeight, camera_origin ),
      m_window( window )
{
    // Init shader
    DefaultAssets::Init();
    TextureCache::Init();

    SetActiveShader(DefaultAssets::default_shader);

    Mesh_Data mesh_data;
    Material_Data mtl_data;
    
    OBJImport::_loadOBJ( "src/game/data/models/Yoshi", &mesh_data, &mtl_data );

    m_mesh = new Mesh(
        m_shader,
        mesh_data,
        mtl_data
    );
    
}

void G_renderer::SetActiveShader( GLShader* glshader ) {
    if (glshader == nullptr) {
        Engine::log::print("[RENDERER] : ",  "TRIED SETTING ACTIVE SHADER AS NULLPTR");

        return;
    }
    
    this->m_shader = glshader;
}

void G_renderer::Render() {
    glClearColor( 0.52f, 0.80f, 0.92f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    m_currentCamera.ComputeMatrix( CAMERA_NEAR_Z, CAMERA_FAR_Z, CAMERA_FOV_DEGREES );
    m_currentCamera.Input( m_window->GetGLFWWindow() );

    m_sceneLight.Render();
    m_mesh->Draw( m_currentCamera );

    //

    glfwSwapBuffers( m_window->GetGLFWWindow() );
    glfwPollEvents();
}

void G_renderer::Destroy() {
    m_sceneLight.Destroy();
}