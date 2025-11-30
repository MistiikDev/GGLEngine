#include "Window.h"
#include "Renderer.h"

void procces_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

Window::Window(const char* WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight) {
    if (!glfwInit()) {
        throw "[GLFW] : FAILED INIT!";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_glfwWindow = glfwCreateWindow(ScreenWidth, ScreenHeight, WindowTitle, NULL, NULL);

    if (!m_glfwWindow) {
        glfwTerminate();
        std::cout << "GLFW_ERR : FAILED WINDOW INIT!";

        return;
    }

    glfwMakeContextCurrent(m_glfwWindow);
    gladLoadGL();
    glViewport(0, 0, ScreenWidth, ScreenHeight);
    glEnable(GL_DEPTH_TEST);

    m_windowRenderer = new Renderer(this, ScreenWidth, ScreenHeight);
}

GLFWwindow* Window::GetGLFWWindow() {
    return m_glfwWindow;
}

void Window::Render() {
    while (!glfwWindowShouldClose(m_glfwWindow)) {
        procces_input(m_glfwWindow);
        m_windowRenderer->Render();
    }

    Destroy();
}

void Window::Destroy() {
    m_windowRenderer->Destroy();

    glfwDestroyWindow(m_glfwWindow);
    glfwTerminate();
}