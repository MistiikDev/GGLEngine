#ifndef GLMaterial_H
#define GLMaterial_H

#include <memory>

#include <render/texture_cache.h>
#include <render/OpenGL/GLTex.h>
#include <global/globals.h>
#include <global/maths/Vector3.h>

struct GLMaterial {

    GLMaterial(  ) = default;

    float specular_factor = 32.0f;

    Vector3 ambiantColor = Vector3(1.0f);
    Vector3 diffuseColor = Vector3(1.0f);
    Vector3 specularColor = Vector3(1.0f);
    Vector3 emissiveColor = Vector3(0.0f);

    std::shared_ptr<GLTex> diffuseTex;
    std::shared_ptr<GLTex> specularTex;

    GLMaterial& SetDiffuse( const Vector3& v )  { diffuseColor = v; return *this; }
    GLMaterial& SetSpecular( const Vector3& v ) { specularColor = v; return *this; }
    GLMaterial& SetAmbient( const Vector3& v )  { ambiantColor = v; return *this; }
    GLMaterial& SetShininess( float s )         { specular_factor = s; return *this; }

    GLMaterial& SetDiffuseTex(const std::string& path) {
        diffuseTex = TextureCache::GetTexture( path.c_str() );
        return *this;
    }

    GLMaterial& SetSpecularTex(const std::string& path) {
        specularTex = TextureCache::GetTexture( path.c_str() );
        return *this;
    }
};

#endif
