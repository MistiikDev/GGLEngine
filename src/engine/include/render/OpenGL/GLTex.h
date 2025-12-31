//
// Created by User on 28/11/2025.
//


#ifndef GLTEX_H
#define GLTEX_H

#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <render/OpenGL/GLShader.h>

class GLTex {
    public:
        int width;
        int height; 
        int colorChannelNum;

        GLuint TextureId;

        GLTex( const char* texturePath );

        void Sample( GLShader& textureShader, GLuint slot, const char* uniform );

        void Bind( GLuint slot );
        void Unbind( GLuint slot );
        void Destroy();
};

#endif