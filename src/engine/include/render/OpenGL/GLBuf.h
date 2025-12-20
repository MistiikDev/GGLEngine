#ifndef GLBUF_H
#define GLBUF_H

#include <glad/glad.h>

#include <iostream>
#include <vector>
#include <type_traits>
#include <global/globals.h>
#include <render/vertex.h>

struct GLBuf {
    GLuint ID;
    GLsizei bufbyteSize;
    GLenum bufType;

    bool b_isEmpty;

    GLBuf();

    template<typename T>
    void BufferData(T& bufData, unsigned int size = 0) {
        const void* ptr_data;

        if constexpr (std::is_same_v<T, std::vector<Vertex>>) {
            this->bufType = GL_ARRAY_BUFFER;
            this->bufbyteSize = sizeof(Vertex) * bufData.size();

            ptr_data = bufData.data();
        
        } else if constexpr (std::is_same_v<T, std::vector<ui32>>) {
            this->bufType = GL_ELEMENT_ARRAY_BUFFER;
            this->bufbyteSize = sizeof(ui32) * bufData.size();

            ptr_data = bufData.data();

        } else if constexpr (std::is_same_v<T, float*> || std::is_same_v<T, unsigned int*>) {
            this->bufType = (std::is_same_v<T, unsigned int*>) ? GL_ELEMENT_ARRAY_BUFFER : GL_ARRAY_BUFFER;
            this->bufbyteSize = size;

            ptr_data = bufData;
        } else {
            Engine::log::print("[OPENGL BUFF] :",  "Tried creating Buffer with unsupported DataType!");
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