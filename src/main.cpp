#include <glad/glad.h>     // Must be first for SOME reason
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include "ShaderInstance.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.H"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

const char* DEFAULT_FRAG_SHADER = "src/Engine/Graphics/Shaders/FShaders/default.frag";
const char* DEFAULT_VERT_SHADER = "src/Engine/Graphics/Shaders/VShaders/default.vert";

const char *vertexShaderSource;
const char *fragShaderSource;

// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices for vertices order
unsigned int indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

void procces_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


int main() {
    if (!glfwInit()) {
        std::cout << "[GLFW] : FAILED INIT!";
        return -1;
    }

    // Window Render
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GGLEngine [ Debugging ]", NULL, NULL);

    if (!window) {
        std::cout << "[GLFW] : FAILED WINDOW!";
        glfwTerminate();
        return -1; 
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 1280, 720);

    // Graphics Render
    ShaderInstance shader {DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER};

    VAO vertexArray {};
    VBO vertexBuffer {vertices};
    EBO elementBuffer {indices};

    vertexArray.Bind();
    vertexArray.LinkVBO(vertexBuffer, 0); // LAYOUT:0

    vertexBuffer.Unbind();
    elementBuffer.Unbind();

    while (!glfwWindowShouldClose(window)) {
        procces_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Activate();
        vertexArray.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader.Destroy();

    vertexArray.Destroy();
    vertexBuffer.Destroy();
    elementBuffer.Destroy();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}