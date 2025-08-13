#include <glad/glad.h>     // Must be first for SOME reason
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cout << "GLFW : FAILED INIT!";
        return -1;
    }
        
    window = glfwCreateWindow(1280, 720, "GLLEngine [ Debugging ]", NULL, NULL);

    if (!window) {
        std::cout << "GLFW : FAILED WINDOW!";
        glfwTerminate();
        return -1; 
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}