//
// Created by User on 28/11/2025.
//

#ifndef GGLENGINE_GLArray_H
#define GGLENGINE_GLArray_H

#include <iostream>
#include <glad/glad.h>

#include "GLBuf.h"

class GLArray {
    public:
        GLuint ID;

        GLArray();

        void Bind();
        void Unbind();
        
        void LinkAttribute(GLBuf& vbo, GLuint layout, unsigned int num_components, GLenum type, GLsizeiptr stride, void* offset);
        void Destroy();
};

#endif