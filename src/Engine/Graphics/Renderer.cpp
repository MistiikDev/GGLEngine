#include "Renderer.h"
#include "Window.h"

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

Renderer::Renderer(Window* window, unsigned int ScreenWidth, unsigned int ScreenHeight)
    : vertexArray(),
      vertexBuffer(vertices, sizeof(vertices)),
      indexBuffer(indices, sizeof(indices)),
      texture0(DEFAULT_TEXTURE, GL_TEXTURE0, GL_TEXTURE_2D, GL_RGB, GL_NEAREST, GL_REPEAT),
      m_shaderInstance(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER),
      m_currentCamera(ScreenWidth, ScreenHeight, camera_origin),
      m_window(window)
{
    vertexArray.Bind();
    indexBuffer.Bind();

    vertexArray.LinkAttribute(vertexBuffer, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vertexArray.LinkAttribute(vertexBuffer, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vertexArray.LinkAttribute(vertexBuffer, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    vertexArray.Unbind();
    vertexBuffer.Unbind();
    indexBuffer.Unbind();

    texture0.Sample(m_shaderInstance, "texture0", 0);
}


void Renderer::Render() {
    glClearColor(0.1f, 0.2f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shaderInstance.Activate();
    m_currentCamera.MatrixRender(CAMERA_NEAR_Z, CAMERA_FAR_Z, CAMERA_FOV_DEGREES, m_shaderInstance, "camera_matrix");
    m_currentCamera.Input(m_window->GetGLFWWindow());

    vertexArray.Bind();
    texture0.Bind();

    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(m_window->GetGLFWWindow());
    glfwPollEvents();
    
}

void Renderer::Destroy() {
    m_shaderInstance.Destroy();

    vertexArray.Destroy();
    vertexBuffer.Destroy();
    indexBuffer.Destroy();

    texture0.Destroy();
}