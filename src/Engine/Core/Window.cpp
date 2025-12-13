#include "Window.h"
#include "Renderer.h"

void procces_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "[GLFW ERROR] code: " << error << " - " << description << std::endl;
}

Window::Window(const char* WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight) {
    if (!glfwInit()) {
        std::cerr << "[DEBUG] glfwInit FAILED\n";
        return;
    }

    glfwSetErrorCallback(glfw_error_callback);
    std::cout << "[DEBUG] glfwInit OK\n";

    m_glfwWindow = glfwCreateWindow(ScreenWidth, ScreenHeight, WindowTitle, NULL, NULL);
    if (!m_glfwWindow) {
        std::cerr << "[DEBUG] glfwCreateWindow FAILED\n";
        glfwTerminate();
        return;
    }

    std::cout << "[DEBUG] glfwCreateWindow OK: " << m_glfwWindow << '\n';

    glfwMakeContextCurrent(m_glfwWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "[DEBUG] glad failed\n";
        glfwDestroyWindow(m_glfwWindow);
        glfwTerminate();
        return;
    }
    
    std::cout << "[DEBUG] glad OK\n";
    std::cout << "OpenGL: " << glGetString(GL_VERSION) << '\n';

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