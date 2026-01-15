//
// Created by User on 28/11/2025.
//


#ifndef GLTEX_H
#define GLTEX_H

#include <iostream>

#include <render/OpenGL/GLShader.h>
#include <render/texture.h>

class GLTex : public Texture {
    public:
        GLuint TextureId;

        GLTex( const char* texturePath );

        void Sample( GLShader& textureShader, GLuint slot, const char* uniform );

        void Bind( GLuint slot );
        void Unbind( GLuint slot );
        void Destroy();
};

#endif