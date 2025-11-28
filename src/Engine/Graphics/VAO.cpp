//
// Created by User on 28/11/2025.
//

#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &this->ID);
}

void VAO::LinkVBO(VBO& vbo, GLuint layout) {
    // Start at index 0, 3 float per vector, dont norm it, 1 stride is 3 * sizeof(float) (x,y,z), and store it at attribute location 0
    vbo.Bind();
    
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
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