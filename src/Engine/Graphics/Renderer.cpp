#include "Renderer.h"
#include "Window.h"

#define CAMERA_FOV_DEGREES 45.0f
#define CAMERA_NEAR_Z 0.1f
#define CAMERA_FAR_Z 100.0f

const glm::vec3 camera_origin = glm::vec3(0.0f, 0.0f, 2.0f);

const char* DEFAULT_FRAG_SHADER = "src/Engine/Graphics/Shaders/FShaders/default.frag";
const char* DEFAULT_VERT_SHADER = "src/Engine/Graphics/Shaders/VShaders/default.vert";

const char* LIGHT_FRAG_SHADER = "src/Engine/Graphics/Shaders/FShaders/light.frag";
const char* LIGHT_VERT_SHADER = "src/Engine/Graphics/Shaders/VShaders/light.vert";

const char* DEFAULT_TEXTURE = "src/Engine/Graphics/Textures/default.jpg";

const char *vertexShaderSource;
const char *fragShaderSource;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


Renderer::Renderer(Window* window, unsigned int ScreenWidth, unsigned int ScreenHeight)
    : vertexArray(),
      vertexBuffer(vertices, sizeof(vertices)),
      indexBuffer(indices, sizeof(indices)),
      texture0(DEFAULT_TEXTURE, GL_TEXTURE0, GL_TEXTURE_2D, GL_RGB, GL_NEAREST, GL_REPEAT),
      m_shaderInstance(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER),
      m_currentCamera(ScreenWidth, ScreenHeight, camera_origin),
      m_window(window),

      m_lightVAO(),
      m_lightVBO(lightVertices, sizeof(lightVertices)),
      m_lightIndexBuffer(lightIndices, sizeof(lightIndices)),
      m_lightShader(LIGHT_VERT_SHADER, LIGHT_FRAG_SHADER)
{
    vertexArray.Bind();
    indexBuffer.Bind();

    vertexArray.LinkAttribute(vertexBuffer, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    vertexArray.LinkAttribute(vertexBuffer, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    vertexArray.LinkAttribute(vertexBuffer, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    vertexArray.LinkAttribute(vertexBuffer, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

    vertexArray.Unbind();
    vertexBuffer.Unbind();
    indexBuffer.Unbind();

    texture0.Sample(m_shaderInstance, "texture0", 0);


    glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 objectTransform = glm::mat4(1.0f);

    objectTransform = glm::translate(objectTransform, objectPos);
    glUniformMatrix4fv(glGetUniformLocation(m_shaderInstance.ID, "vertexTransform"), 1, GL_FALSE, glm::value_ptr(objectTransform));


    // 
    // Spawn a light cube for debugging light rendering
    m_lightVAO.Bind();    
    m_lightIndexBuffer.Bind();

    m_lightVAO.LinkAttribute(m_lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)(0));
        
    m_lightVAO.Unbind();
    m_lightVBO.Unbind();
    m_lightIndexBuffer.Unbind();

    m_lightShader.Activate();
    glm::mat4 lightTransform = glm::mat4(1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    lightTransform = glm::translate(lightTransform, lightPos);

    // Send light data to light shaders
    glUniformMatrix4fv(glGetUniformLocation(m_lightShader.ID, "light_transform"), 1, GL_FALSE, glm::value_ptr(lightTransform));
    glUniform4f(glGetUniformLocation(m_lightShader.ID, "light_color"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
}


void Renderer::Render() {
    glClearColor(0.1f, 0.2f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shaderInstance.Activate();

    m_currentCamera.ComputeMatrix(CAMERA_NEAR_Z, CAMERA_FAR_Z, CAMERA_FOV_DEGREES);
    m_currentCamera.Input(m_window->GetGLFWWindow());
    m_currentCamera.MatrixRender(m_shaderInstance, "camera_matrix");

    vertexArray.Bind();
    texture0.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    
    //
    // Send camera matrix to light shaders
    m_lightShader.Activate();
    m_currentCamera.MatrixRender(m_lightShader, "camera_matrix");

    
    m_lightVAO.Bind();
    m_lightIndexBuffer.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);



    //
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