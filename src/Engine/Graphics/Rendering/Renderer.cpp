#include "Renderer.h"
#include "Window.h"

#define CAMERA_FOV_DEGREES 45.0f
#define CAMERA_NEAR_Z 0.1f
#define CAMERA_FAR_Z 100.0f

const glm::vec3 camera_origin = glm::vec3(0.0f, 0.0f, 2.0f);

const char* DEFAULT_FRAG_SHADER = "src/Engine/Graphics/Shaders/FShaders/default.frag";
const char* DEFAULT_VERT_SHADER = "src/Engine/Graphics/Shaders/VShaders/default.vert";

Renderer::Renderer(Window* window, unsigned int ScreenWidth, unsigned int ScreenHeight)
    : vertexArray(),  //texture0(DEFAULT_TEXTURE, GL_TEXTURE0, GL_TEXTURE_2D, GL_RGB, GL_NEAREST, GL_REPEAT),
      m_sceneLight(glm::vec3(0.5f)),
      m_shaderInstance(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER),
      m_currentCamera(ScreenWidth, ScreenHeight, camera_origin),
      m_window(window)
{
    OBJ_Data testMesh = OBJImport::_loadOBJ("src/Models/Cop.obj");

    this->vertexBuffer = VBO { testMesh.vertices };
    this->indexBuffer = EBO { testMesh.indicies };

    std::cout << this->vertexBuffer.totalByteSize << std::endl;
    std::cout << this->vertexBuffer.totalByteSize << std::endl;

    vertexArray.Bind();
    indexBuffer.Bind();

    vertexArray.LinkAttribute(vertexBuffer, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    vertexArray.LinkAttribute(vertexBuffer, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    vertexArray.LinkAttribute(vertexBuffer, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    vertexArray.LinkAttribute(vertexBuffer, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

    vertexArray.Unbind();
    vertexBuffer.Unbind();
    indexBuffer.Unbind();

    glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 objectTransform = glm::mat4(1.0f);
    objectTransform = glm::translate(objectTransform, objectPos);

    m_shaderInstance.Activate();
    
    m_shaderInstance.SetMatrix4f("vertexTransform", objectTransform);
    m_shaderInstance.SetVector3f("light_color", m_sceneLight.lightColor);
    m_shaderInstance.SetVector3f("light_position", m_sceneLight.lightCFrame.Position);
}

void Renderer::Render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_currentCamera.ComputeMatrix(CAMERA_NEAR_Z, CAMERA_FAR_Z, CAMERA_FOV_DEGREES);
    m_currentCamera.Input(m_window->GetGLFWWindow());

    //

    m_shaderInstance.Activate();
    m_shaderInstance.SetVector3f("light_color", m_sceneLight.lightColor);
    m_shaderInstance.SetVector3f("light_position", m_sceneLight.lightCFrame.Position);

    m_shaderInstance.SetVector3f("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    m_shaderInstance.SetVector3f("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    m_shaderInstance.SetVector3f("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    m_shaderInstance.SetFloat("material.shininess", 32.0f);

    m_currentCamera.MatrixRender(m_shaderInstance, "camera_matrix");

    vertexArray.Bind();
    indexBuffer.Bind();
    glDrawElements(GL_TRIANGLES, indexBuffer.totalByteSize / sizeof(uint32_t), GL_UNSIGNED_INT, 0);


    // 
    m_sceneLight.Render();

    //
    glfwSwapBuffers(m_window->GetGLFWWindow());
    glfwPollEvents();
}

void Renderer::Destroy() {
    m_shaderInstance.Destroy();
    m_sceneLight.Destroy();

    vertexArray.Destroy();
    vertexBuffer.Destroy();
    indexBuffer.Destroy();
}