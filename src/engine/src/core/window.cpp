#include <core/scene_window.h>
#include <render/scene_renderer.h>

EditorViewport::EditorViewport( const char* WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight ) {
    if (!glfwInit()) {
        Engine::log::print("[GLFW ERROR] : ", "FAILED INIT");
        return;
    }

    glfwSetErrorCallback(Engine::glfw::glfw_error_callback);

    m_glfwWindow = glfwCreateWindow(ScreenWidth, ScreenHeight, WindowTitle, NULL, NULL);
    if (!m_glfwWindow) {
        Engine::log::print("[GLFW ERROR] : ", "FAILED WINDOW CREATION");
        glfwTerminate();
        return;
    }

    Engine::log::print("[GLFW DEBUG] : ", "WINDOW OK", " ( ", m_glfwWindow, " )");

    glfwMakeContextCurrent(m_glfwWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Engine::log::print("[GLAD ERROR] : ", "FAILURE");

        glfwDestroyWindow(m_glfwWindow);
        glfwTerminate();
        return;
    }
    
    Engine::log::print("[OPENGL] : ", glGetString(GL_VERSION));

    gladLoadGL();

    // --- IMGUI INIT START ---
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
    // Enable Keyboard Controls

    ImGui::StyleColorsDark(); 

    ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    // --- IMGUI INIT END ---

    glViewport(0, 0, ScreenWidth, ScreenHeight);
    glEnable(GL_DEPTH_TEST);

    m_mouseState = MOUSE_FOCUS;
    m_viewportRenderer = std::make_unique<SceneRenderer>(this, ScreenWidth, ScreenHeight);
}

GLFWwindow* EditorViewport::GetGLFWWindow() {
    return m_glfwWindow;
}

void EditorViewport::Input() {
    ImGuiIO io = ImGui::GetIO();

    if (glfwGetKey(m_glfwWindow, GLFW_KEY_F) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    } else if (glfwGetKey(m_glfwWindow, GLFW_KEY_F) == GLFW_RELEASE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (glfwGetMouseButton(m_glfwWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (!io.WantCaptureMouse) {
            m_mouseState = MOUSE_FOCUS;
        }
    } else if (glfwGetKey(m_glfwWindow, GLFW_KEY_ESCAPE)) {
        m_mouseState = MOUSE_FREE;
    }

    if (m_mouseState == MOUSE_FOCUS) {
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void EditorViewport::Render() {
    while (!glfwWindowShouldClose(m_glfwWindow)) {
        this->Input();

        m_viewportRenderer->Render();
    }

    Destroy();
}

void EditorViewport::Destroy() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    m_viewportRenderer->Destroy();

    glfwDestroyWindow(m_glfwWindow);
    glfwTerminate();
}