#include <core/window.h>
#include <render/renderer.h>

void procces_input( GLFWwindow *window ) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    } else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    } else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
    }
}

static void glfw_error_callback( int error, const char* description ) {
    Engine::log::print("[GLFW ERROR] : ", error, description);
}

G_window::G_window( const char* WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight ) {
    if (!glfwInit()) {
        Engine::log::print("[GLFW ERROR] : ", "FAILED INIT");
        return;
    }

    glfwSetErrorCallback(glfw_error_callback);

    m_glfwWindow = glfwCreateWindow(ScreenWidth, ScreenHeight, WindowTitle, NULL, NULL);
    if (!m_glfwWindow) {
        Engine::log::print("[GLFW ERROR] : ", "FAILED WINDOW CREATION");
        glfwTerminate();
        return;
    }

    Engine::log::print("[GLFW DEBUG] : ", "WINDOW OK", m_glfwWindow);

    glfwMakeContextCurrent(m_glfwWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Engine::log::print("[GLAD ERROR] : ", "FAILURE");

        glfwDestroyWindow(m_glfwWindow);
        glfwTerminate();
        return;
    }
    
    Engine::log::print("[OPENGL] : ", glGetString(GL_VERSION));

    gladLoadGL();
    glViewport(0, 0, ScreenWidth, ScreenHeight);
    glEnable(GL_DEPTH_TEST);

    m_windowRenderer = new G_renderer(this, ScreenWidth, ScreenHeight);
}

GLFWwindow* G_window::GetGLFWWindow() {
    return m_glfwWindow;
}

void G_window::Render() {
    while (!glfwWindowShouldClose(m_glfwWindow)) {
        procces_input(m_glfwWindow);
        m_windowRenderer->Render();
    }

    Destroy();
}

void G_window::Destroy() {
    m_windowRenderer->Destroy();

    glfwDestroyWindow(m_glfwWindow);
    glfwTerminate();
}