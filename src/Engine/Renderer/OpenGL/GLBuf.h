#ifndef GGLENGINE_GLBUG_H
#define GGLENGINE_GLBUG_H

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <type_traits>

#include "Vertex.h"

struct GLBuf {
    GLuint ID;
    GLsizei bufbyteSize;
    GLenum bufType;

    bool b_isEmpty;

    GLBuf();

    template<typename T>
    void BufferData(T bufData, unsigned int size = 0) {
        const void* ptr_data;

        if (std::is_same_v<T, std::vector<Vertex>>) {
            this->bufType = GL_ARRAY_BUFFER;
            this->bufbyteSize = bufData.size() * sizeof(Vertex);

            ptr_data = bufData.data();
        
        } else if (std::is_same_v<T, std::vector<uint32_t>>) {
            this->bufType = GL_ELEMENT_ARRAY_BUFFER;
            this->bufbyteSize = sizeof(uint32_t) * bufData.size();

            ptr_data = bufData.data();

        } else if (std::is_same_v<T, float*> || std::is_same_v<T, unsigned int*>) {
            this->bufType = (std::is_same_v<T, unsigned int*>) ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER;
            this->bufbyteSize = size;

            ptr_data = bufData;
        } else {
            std::cout << "[OPENGL BUFF] : Tried creating Buffer with unsupported DataType!" << std::endl;
            throw EXIT_FAILURE;
        }

        glGenBuffers(1, &this->ID);

        glBindBuffer(bufType, this->ID);
        glBufferData(bufType, bufbyteSize, ptr_data, GL_STATIC_DRAW);

        glBindBuffer(bufType, 0);

        this->b_isEmpty = false;
    }

    void Bind();
    void Unbind();

    void Destroy();
};

#endif