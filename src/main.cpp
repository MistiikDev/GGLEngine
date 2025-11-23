#include <glad/glad.h>     // Must be first for SOME reason
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"

    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\0";

float triangle_verticies[] = {
    // first triangle
     0.5f,  0.5f, 0.0f,  
     0.5f, -0.5f, 0.0f,  
    -0.5f,  0.5f, 0.0f,  

    // second triangle
     0.5f, -0.5f, 0.0f,  
    -0.5f, -0.5f, 0.0f,  
    -0.5f,  0.5f, 0.0f   
};

unsigned int triangles_indices[] = {
    0, 1, 2,
    1, 2, 3
};

void procces_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

unsigned int process_shaders() {
    // Create GPU vertex shader and fragment shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create Shader Program, Attach + Link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main() {
    if (!glfwInit()) {
        std::cout << "GLFW : FAILED INIT!";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GLLEngine [ Debugging ]", NULL, NULL);

    if (!window) {
        std::cout << "GLFW : FAILED WINDOW!";
        glfwTerminate();
        return -1; 
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 1280, 720);

    unsigned int shaderProgram = process_shaders();
    unsigned int VAO, VBO, EBO;
    // Bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_verticies), triangle_verticies, GL_STATIC_DRAW);

    // Pass vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
    // Start at index 0, 3 float per vector, dont norm it, 1 stride is 3 * sizeof(float) (x,y,z), and store it at attribute location 0

    glEnableVertexAttribArray(0); // Enable Attribute 0 (position) 

    // Bind EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles_indices), triangles_indices, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window)) {
        procces_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glUseProgram(shaderProgram);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}