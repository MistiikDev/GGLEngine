//
// Created by User on 28/11/2025.
//


#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <render/OpenGL/GLShader.h>

class Texture {
    public:
        int width;
        int height; 

        int colorChannelNum;

        GLuint TextureId;
        GLenum TextureType;

        Texture(const char* texturePath, GLuint slot, GLenum textureType, GLenum textureFormat, GLenum textureScaleType, GLenum textureWrapType);

        void Sample(GLShader& textureShader, const char* uniform, GLuint textureUnitSlot);

        void Bind();
        void Unbind();
        void Destroy();
};

#endif