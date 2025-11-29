//
// Created by User on 28/11/2025.
//

#include "EBO.h"

EBO::EBO(unsigned int* indicies, unsigned int size) {
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicies, GL_STATIC_DRAW);
}

void EBO::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}

void EBO::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Destroy() {
    glDeleteBuffers(1, &this->ID);
}