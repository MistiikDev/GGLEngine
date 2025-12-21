#include <render/renderer.h>
#include <core/window.h>

#define CAMERA_FOV_DEGREES 45.0f
#define CAMERA_NEAR_Z 0.1f
#define CAMERA_FAR_Z 100.0f

const glm::vec3 camera_origin = glm::vec3(0.0f, 0.0f, 2.0f);

G_renderer::G_renderer( G_window* window, unsigned int ScreenWidth, unsigned int ScreenHeight )
    : m_sceneLight( glm::vec3(0.5f, 2.5f, 0.5f) ),
      m_currentCamera( ScreenWidth, ScreenHeight, camera_origin ),
      m_window( window )
{
    GLShader* default_shader = new GLShader { DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER };


    OBJ_Data obj_data;
    MTL_Data mtl_data;
    
    OBJImport::_loadOBJ( "src/game/data/models/Cop", &obj_data, &mtl_data );

    m_mesh = new Mesh(
        default_shader,
        obj_data.vertices,
        obj_data.indicies,
        mtl_data.materials
    );
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