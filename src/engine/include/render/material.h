#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include <render/OpenGL/GLTex.h>
#include <global/globals.h>
#include <global/maths/Vector3.h>

struct Material {

    Material(  ) = default;

    float specular_factor = 32.0f;

    Vector3 ambiantColor = Vector3(1.0f);
    Vector3 diffuseColor = Vector3(1.0f);
    Vector3 specularColor = Vector3(1.0f);
    Vector3 emissiveColor = Vector3(0.0f);

    std::shared_ptr<GLTex> diffuseTex;
    std::shared_ptr<GLTex> specularTex;

    Material& SetDiffuse( const Vector3& v )  { diffuseColor = v; return *this; }
    Material& SetSpecular( const Vector3& v ) { specularColor = v; return *this; }
    Material& SetAmbient( const Vector3& v )  { ambiantColor = v; return *this; }
    Material& SetShininess( float s )         { specular_factor = s; return *this; }

    Material& SetDiffuseTex(const std::string& path) {
        diffuseTex = std::make_shared<GLTex>(path.c_str());
        return *this;
    }

    Material& SetSpecularTex(const std::string& path) {
        specularTex = std::make_shared<GLTex>(path.c_str());
        return *this;
    }
};

#endif
