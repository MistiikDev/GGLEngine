#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include <global/maths/Vector3.h>
#include <render/texture_cache.h>
#include <render/texture.h>

#include <global/globals.h>

struct Material {
    Material(  ) = default;

    float specular_factor = 32.0f;

    Vector3 ambiantColor = Vector3(1.0f);
    Vector3 diffuseColor = Vector3(1.0f);
    Vector3 specularColor = Vector3(1.0f);
    Vector3 emissiveColor = Vector3(0.0f);

    virtual Material& SetDiffuse( const Vector3& v )  { diffuseColor = v; return *this; }
    virtual Material& SetSpecular( const Vector3& v ) { specularColor = v; return *this; }
    virtual Material& SetAmbient( const Vector3& v )  { ambiantColor = v; return *this; }
    virtual Material& SetShininess( float s )         { specular_factor = s; return *this; }

    std::shared_ptr<Texture> diffuseTex;
    std::shared_ptr<Texture> specularTex;

    Material& SetDiffuseTex(const std::string& path) {
        diffuseTex = TextureCache::GetTexture( path.c_str() );
        return *this;
    }

    Material& SetSpecularTex(const std::string& path) {
        specularTex = TextureCache::GetTexture( path.c_str() );
        return *this;
    }
};

#endif