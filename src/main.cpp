#include <glad/glad.h>     // Must be first for SOME reason
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "ShaderInstance.h"
#include "Texture.h"
#include "Camera.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.H"



#define FRAME_RATE 24

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define CAMERA_FOV_DEGREES 45.0f
#define CAMERA_NEAR_Z 0.1f
#define CAMERA_FAR_Z 100.0f

const glm::vec3 camera_origin = glm::vec3(0.0f, 0.0f, 2.0f);





const char* DEFAULT_FRAG_SHADER = "src/Engine/Graphics/Shaders/FShaders/default.frag";
const char* DEFAULT_VERT_SHADER = "src/Engine/Graphics/Shaders/VShaders/default.vert";

const char* DEFAULT_TEXTURE = "src/Engine/Graphics/Textures/default.jpg";

const char *vertexShaderSource;
const char *fragShaderSource;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	0.5f, 1.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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
    glEnable(GL_DEPTH_TEST); // Enable depth buffer (weird perspective otherwise)

    // Graphics Render
    ShaderInstance shader { DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER };

    VAO vertexArray {};
    vertexArray.Bind();

    VBO vertexBuffer { vertices, sizeof(vertices) };
    EBO elementBuffer { indices, sizeof(indices) };

    vertexArray.LinkAttribute(vertexBuffer, 0, 3, GL_FLOAT, 8 * sizeof(GL_FLOAT), (void*)0); // LAYOUT:0 (position 3D)
    vertexArray.LinkAttribute(vertexBuffer, 1, 3, GL_FLOAT, 8 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT))); // LAYOUT:1 (color 3D)
    vertexArray.LinkAttribute(vertexBuffer, 2, 2, GL_FLOAT, 8 * sizeof(GL_FLOAT), (void*)(6 * sizeof(GL_FLOAT))); // LAYOUT:2 (texture position 2D)

    Texture tex0 { DEFAULT_TEXTURE, GL_TEXTURE0, GL_TEXTURE_2D, GL_RGB, GL_NEAREST, GL_REPEAT }; 
    Camera camera { SCREEN_WIDTH, SCREEN_HEIGHT, camera_origin };

    tex0.Sample(shader, "texture0", 0);

    while (!glfwWindowShouldClose(window)) {
        procces_input(window);

        glClearColor(0.1f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        shader.Activate();

        
        camera.MatrixRender(CAMERA_NEAR_Z, CAMERA_FAR_Z, CAMERA_FOV_DEGREES, shader, "camera_matrix");
        camera.Input(window);


        vertexArray.Bind();
        tex0.Bind();


        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader.Destroy();

    vertexArray.Destroy();
    vertexBuffer.Destroy();
    elementBuffer.Destroy();

    tex0.Destroy();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}