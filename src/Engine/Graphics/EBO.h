//
// Created by User on 28/11/2025.
//

#ifndef GGLENGINE_EBO_H
#define GGLENGINE_EBO_H

#include <iostream>
#include <glad/glad.h>

class EBO {
    public:
        GLuint ID;
        EBO(unsigned int* indicies);

        void Bind();
        void Unbind();

        void Destroy();
};

#endif