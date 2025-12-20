//
// Created by User on 28/11/2025.
//


#ifndef GLShader_H
#define GLShader_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <global/globals.h>
#include <global/maths/Vector3.h>

std::string get_shader_code(const char* shaderFile);

class GLShader
{
    public:
        GLuint ID;
        GLShader(const char* vertexShader, const char* fragmentShader);

        void SetFloat(const char* uniform, const float value);
        void SetMatrix4f(const char* uniform, const glm::mat4& matrix);
        void SetVector3f(const char* uniform, const glm::vec3& vector);
        void SetVector3f(const char* uniform, const Vector3& vector);
        
        void CompilationErrors(unsigned int ShaderID, const char* shaderCompilationType);

        void Activate();
        void Destroy();

    private:
        bool m_isActive;
};


#endif //GGLENGINE_GLShader_H