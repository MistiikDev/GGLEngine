//
// Created by User on 28/11/2025.
//

#ifndef GGLENGINE_VBO_H
#define GGLENGINE_VBO_H

#include <iostream>
#include <glad/glad.h>

class VBO {
    public:
        GLuint ID;
        VBO(float* verticies);

        void Bind();
        void Unbind();

        void Destroy();
};

#endif