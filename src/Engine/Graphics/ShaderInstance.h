//
// Created by User on 28/11/2025.
//

#ifndef GGLENGINE_SHADERINSTANCE_H
#define GGLENGINE_SHADERINSTANCE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <glad/glad.h>

std::string get_shader_code(const char* shaderFile);

class ShaderInstance
{
    public:
        GLuint ID;
        ShaderInstance(const char* vertexShader, const char* fragmentShader);

        void CompilationErrors(unsigned int ShaderID, const char* shaderCompilationType);

        void Activate();
        void Destroy();
};


#endif //GGLENGINE_SHADERINSTANCE_H