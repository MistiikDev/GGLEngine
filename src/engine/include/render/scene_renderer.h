#ifndef RENDERER_H
#define RENDERER_H

#include <stb/stb_image.h>
#include <iostream>
#include <memory>

#include <asset/default_assets.h>
#include <api/bootstrap/dependencies/graphics.h>

#include <core/camera.h>
#include <scene/lighting/point_light.h>
#include <render/texture.h>
#include <global/globals.h>

struct RenderContext {
    GLShader* m_shader;
    Camera* m_currentCamera;

    RENDER_ENGINE rendering_api;

    std::unordered_map<std::shared_ptr<Texture>, int> textureSlotMap;
};

class EditorViewport;
class SceneRenderer {
    public: 
        SceneRenderer( EditorViewport* m_viewport, unsigned int ScreenWidth, unsigned int ScreenHeight );

        Camera* CurrentCamera( ) { return &m_currentCamera; }

        void SetActiveShader( GLShader* glshader );
        void Render();
        void Destroy();
    private:
        EditorViewport* m_viewport;
        GLShader* m_shader;

        Camera m_currentCamera;
        PointLight m_sceneLight;
};

#endif