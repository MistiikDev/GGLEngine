#include <glad/glad.h>     // Must be first for SOME reason
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb/stb_image.h>

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
GLfloat vertices[] = // POSITION // COLOR
{
	-0.5f, 0.5f, 0.0f,          0.1f, 0.1f, 0.5f,  // Lower left corner
	-0.5f, -0.5f, 0.0f,         0.8f, 0.2f, 0.3f,  // Lower right corner
	0.5f, 0.5f , 0.0f,          0.3f, 0.3f, 0.4f,  // Upper corner
	0.5f, -0.5f, 0.0f,          0.5f, 0.8f, 0.2f,  // Inner left
};

// Indices for vertices order
unsigned int indices[] =
{
    0, 2, 3,
    3, 1, 0
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
    vertexArray.Bind();

    VBO vertexBuffer {vertices, sizeof(vertices)};
    EBO elementBuffer {indices, sizeof(indices)};

    vertexArray.LinkAttribute(vertexBuffer, 0, 3, GL_FLOAT, 6 * sizeof(GL_FLOAT), (void*)0); // LAYOUT:0 (position)
    vertexArray.LinkAttribute(vertexBuffer, 1, 3, GL_FLOAT, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT))); // LAYOUT:1 (color)
    
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