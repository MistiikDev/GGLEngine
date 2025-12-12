//
// Created by User on 28/11/2025.
//

#ifndef GGLENGINE_VBO_H
#define GGLENGINE_VBO_H

#include <iostream>
#include <vector>
#include <glad/glad.h>

#include "Vertex.h"

class VBO {
    public:
        GLuint ID;
        uint32_t totalByteSize;
        
        VBO() = default;
        VBO(float* verticies, unsigned int size);
        VBO(std::vector<Vertex> verticies);

        void Bind();
        void Unbind();

        void Destroy();
};

#endif