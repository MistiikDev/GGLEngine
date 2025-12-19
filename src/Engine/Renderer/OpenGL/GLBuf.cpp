#include "GLBuf.h"

GLBuf::GLBuf() {
    b_isEmpty = true;
}

void GLBuf::Bind() {
    if (b_isEmpty) {
        std::cout << "[OPENGL BUF] : CANNOT BIND EMPTY BUFFER OBJECT\n";

        return;
    }

    glBindBuffer(bufType, ID);
}

void GLBuf::Unbind() {
    if (b_isEmpty) {
        std::cout << "[OPENGL BUF] : CANNOT UNBIND EMPTY BUFFER OBJECT\n";

        return;
    }

    glBindBuffer(bufType, 0);
}

void GLBuf::Destroy() {
    if (b_isEmpty) {
        std::cout << "[OPENGL BUF] : CANNOT DESTROY EMPTY BUFFER OBJECT\n";

        return;
    }

    glDeleteBuffers(1, &this->ID);
}