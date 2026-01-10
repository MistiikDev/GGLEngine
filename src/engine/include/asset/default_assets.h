#ifndef DEFAULT_ASSETS_H
#define DEFAULT_ASSETS_H

#define DEFAULT_VERT_SHADER "src/game/src/data/shaders/VShaders/default.vert"
#define DEFAULT_FRAG_SHADER "src/game/src/data/shaders/FShaders/default.frag"

#define DEBUG_TEXTURE_PATH "src/engine/src/asset/default_assets/debug_texture.png"
#define WHITE_TEXTURE_PATH "src/engine/src/asset/default_assets/white_texture.png"

#include <memory>

#include <render/texture_cache.h>
#include <render/OpenGL/GLMaterial.h>
#include <render/OpenGL/GLShader.h>
#include <render/OpenGL/GLTex.h>

struct DefaultAssets {
    static inline GLMaterial* debug_GLMaterial;
    static inline GLMaterial* white_GLMaterial;

    static inline std::shared_ptr<GLTex> debug_texture;
    static inline std::shared_ptr<GLTex> white_texture;

    static inline GLShader* default_shader;

    static void Init() {
        default_shader = new GLShader { DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER };
        
        debug_GLMaterial = new GLMaterial();
        debug_GLMaterial->SetDiffuseTex( DEBUG_TEXTURE_PATH );
        debug_GLMaterial->SetSpecularTex( DEBUG_TEXTURE_PATH );

        // These textures are shared, thus not taking the latter option of retaking them
        white_texture = TextureCache::GetTexture ( WHITE_TEXTURE_PATH ) ;
        debug_texture = TextureCache::GetTexture ( DEBUG_TEXTURE_PATH ) ;

        Engine::log::print("[ENGINE] : ", "Default Assets Loaded");
    }

    static void Destroy() {
        
    }
};

#endif // DEFAULT_ASSETS_H