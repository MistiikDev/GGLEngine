//
// Created by User on 28/11/2025.
//

#ifndef GGLENGINE_VAO_H
#define GGLENGINE_VAO_H

#include <iostream>
#include <glad/glad.h>

#include "VBO.h"

class VAO {
    public:
        GLuint ID;

        VAO();

        void Bind();
        void Unbind();
        
        void LinkVBO(VBO& vbo, GLuint layout);

        void Destroy();
};

#endif