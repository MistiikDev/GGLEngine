//
// Created by User on 28/11/2025.
//

#ifndef GGLENGINE_EBO_H
#define GGLENGINE_EBO_H

#include <iostream>
#include <vector>
#include <glad/glad.h>

class EBO {
    public:
        GLuint ID;
        uint32_t totalByteSize;
        
        EBO() = default;
        EBO(unsigned int* indicies, unsigned int size);
        EBO(std::vector<uint16_t> verticies);

        void Bind();
        void Unbind();

        void Destroy();
};

#endif