#ifndef DEFAULT_ASSETS_H
#define DEFAULT_ASSETS_H

#define DEFAULT_VERT_SHADER "src/game/data/shaders/VShaders/default.vert"
#define DEFAULT_FRAG_SHADER "src/game/data/shaders/FShaders/default.frag"

#define DEBUG_TEXTURE_PATH "src/engine/src/asset/default_assets/debug_texture.png"
#define WHITE_TEXTURE_PATH "src/engine/src/asset/default_assets/white_texture.png"

#include <memory>

#include <render/material.h>
#include <render/OpenGL/GLShader.h>
#include <render/OpenGL/GLTex.h>

struct DefaultAssets {
    static inline Material* debug_material;
    static inline Material* white_material;

    static inline std::shared_ptr<GLTex> debug_texture;
    static inline std::shared_ptr<GLTex> white_texture;

    static inline GLShader* default_shader;

    static void Init() {

        default_shader = new GLShader { DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER };
        
        debug_material = new Material();
        debug_material->SetDiffuseTex( DEBUG_TEXTURE_PATH );
        debug_material->SetSpecularTex( DEBUG_TEXTURE_PATH );

        // These textures are shared, thus not taking the latter option of retaking them
        white_texture = std::make_shared<GLTex> ( WHITE_TEXTURE_PATH ) ;
        debug_texture = std::make_shared<GLTex> ( DEBUG_TEXTURE_PATH ) ;
    }

    static void Destroy() {
        delete debug_material;
        delete default_shader;
    }
};

#endif // DEFAULT_ASSETS_H