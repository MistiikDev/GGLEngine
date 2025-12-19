//
// Created by User on 28/11/2025.
//

#include "GLArray.h"

GLArray::GLArray() {
    glGenVertexArrays(1, &this->ID);
}

void GLArray::LinkAttribute(GLBuf& vbo, GLuint layout, unsigned int num_components, GLenum type, GLsizeiptr stride, void* offset) {
    vbo.Bind();
    
    glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout); // All data will be passed through index "layout" for gl to read
    
    vbo.Unbind();
}

void GLArray::Bind() {
    glBindVertexArray(this->ID);
}

void GLArray::Unbind() {
    glBindVertexArray(0);
}

void GLArray::Destroy() {
    glDeleteVertexArrays(1, &this->ID);
}