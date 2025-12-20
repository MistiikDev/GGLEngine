//
// Created by User on 28/11/2025.
//

#include <render/OpenGL/GLShader.h>

GLShader::GLShader(const char* vertexShader, const char* fragShader) {
    std::string vertexCode = get_shader_code(vertexShader);
    std::string fragCode = get_shader_code(fragShader);

    std::cout << "[SHADER LOADED] Vertex Shader : " << vertexShader << "\n";
    std::cout << "[SHADER LOADED] Fragment Shader : " << fragShader << "\n";

    const char* vertexSource = vertexCode.c_str();
    const char* fragSource = fragCode.c_str();

    unsigned int vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderObject, 1, &vertexSource, NULL);
    glCompileShader(vertexShaderObject);

    this->CompilationErrors(vertexShaderObject, "PROGRAM");

    unsigned int fragShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShaderObject, 1, &fragSource, NULL);
    glCompileShader(fragShaderObject);

    this->CompilationErrors(fragShaderObject, "PROGRAM");

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderObject);
    glAttachShader(shaderProgram, fragShaderObject);
    glLinkProgram(shaderProgram);

    this->CompilationErrors(shaderProgram, "LINKING");

    this->ID = shaderProgram;

    glDeleteShader(vertexShaderObject);
    glDeleteShader(fragShaderObject);
}

void GLShader::SetMatrix4f(const char* uniform, const glm::mat4& matrix) {
    if (!this->m_isActive) { 
        std::cout << "SHADER_COMPILATION_ERR  : Tried accessing shader when not active!\n";

        throw;
    }

    glUniformMatrix4fv(glGetUniformLocation(this->ID, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
}

void GLShader::SetVector3f(const char* uniform, const Vector3& vector) {
    if (!this->m_isActive) { 
        std::cout << "SHADER_COMPILATION_ERR  : Tried accessing shader when not active!\n";

        throw;
    }

    glUniform3f(glGetUniformLocation(this->ID, uniform), vector.x, vector.y, vector.z);
}

void GLShader::SetVector3f(const char* uniform, const glm::vec3& vector) {
    if (!this->m_isActive) { 
        std::cout << "SHADER_COMPILATION_ERR  : Tried accessing shader when not active!\n";

        throw;
    }

    glUniform3f(glGetUniformLocation(this->ID, uniform), vector.x, vector.y, vector.z);
}

void GLShader::SetFloat(const char* uniform, const float value) {
    if (!this->m_isActive) { 
        std::cout << "SHADER_COMPILATION_ERR  : Tried accessing shader when not active!\n";

        throw;
    }

    glUniform1f(glGetUniformLocation(this->ID, uniform), value);
}

void GLShader::Activate() {
    this->m_isActive = true;

    glUseProgram(this->ID);
}

void GLShader::Destroy() {
    this->m_isActive = false;
    
    glDeleteProgram(this->ID);
}

std::string get_shader_code(const char* shaderFile) {
    std::ifstream file(shaderFile);

    if (!file) {
        throw std::runtime_error("[SHADER_ERR]: Failed to open shader file.");
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); 

    return buffer.str();
}


void GLShader::CompilationErrors(unsigned int ShaderID, const char* shaderCompilationType) {
    GLint hasCompiled;
    size_t infoLogBufSize = 512;
    char infoLog[infoLogBufSize];

    if (shaderCompilationType == "PROGRAM") {
        glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &hasCompiled);

        if (hasCompiled == GL_FALSE) {
            glGetShaderInfoLog(ShaderID, infoLogBufSize, NULL, infoLog);

            Engine::log::print("[GLSHADER ERR]", "SHADER_COMPILATION_ERR  : ", std::string(infoLog));
        }
    } else {
        glGetProgramiv(ShaderID, GL_COMPILE_STATUS, &hasCompiled);

        if (hasCompiled == GL_FALSE) {
            glGetProgramInfoLog(ShaderID, infoLogBufSize, NULL, infoLog);

            Engine::log::print("[GLSHADER ERR]", "SHADER_LINK_ERR  : ", std::string(infoLog));
        }
    }

}