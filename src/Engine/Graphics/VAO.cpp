//
// Created by User on 28/11/2025.
//

#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &this->ID);
}

void VAO::LinkAttribute(VBO& vbo, GLuint layout, unsigned int num_components, GLenum type, GLsizeiptr stride, void* offset) {
    vbo.Bind();
    
    glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout); // All data will be passed through index "layout" for gl to read
    
    vbo.Unbind();
}

void VAO::Bind() {
    glBindVertexArray(this->ID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::Destroy() {
    glDeleteVertexArrays(1, &this->ID);
}