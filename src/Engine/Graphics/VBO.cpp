//
// Created by User on 28/11/2025.
//

#include "VBO.h"

VBO::VBO(float* verticies, unsigned int size) {
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);

    glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);

    totalByteSize = size;
}

VBO::VBO(std::vector<Vertex> verticies) {
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);

    totalByteSize = verticies.size() * sizeof(Vertex);

    const void* rawDataPtr = verticies.data();

    glBufferData(GL_ARRAY_BUFFER, totalByteSize, rawDataPtr, GL_STATIC_DRAW);
}

void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Destroy() {
    glDeleteBuffers(1, &this->ID);
}