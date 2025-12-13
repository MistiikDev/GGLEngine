#include "Mesh.h"

const char* DEFAULT_FRAG_SHADER = "src/Engine/Graphics/Shaders/FShaders/default.frag";
const char* DEFAULT_VERT_SHADER = "src/Engine/Graphics/Shaders/VShaders/default.vert";

Mesh::Mesh(std::vector<Vertex> in_verticies, std::vector<uint16_t> in_indicies)
    : m_shader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER)
{
    verticies = in_verticies;
    indicies = in_indicies;

    m_modelVertexArray = VAO {};
    m_modelBuffer = VBO { verticies };
    m_modelIndexBuffer = EBO { indicies };

    m_modelVertexArray.Bind();
    m_modelBuffer.Bind();
    m_modelIndexBuffer.Bind();

    m_modelVertexArray.LinkAttribute(m_modelBuffer, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0); // Position Attribute
    m_modelVertexArray.LinkAttribute(m_modelBuffer, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)( 3 * sizeof(float))); // Color Attribute
    m_modelVertexArray.LinkAttribute(m_modelBuffer, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)( 6 * sizeof(float))); // TexUV Attribute
    m_modelVertexArray.LinkAttribute(m_modelBuffer, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)( 8 * sizeof(float))); // Normal Attribute

    m_modelVertexArray.Unbind();
    m_modelBuffer.Unbind();
    m_modelIndexBuffer.Unbind();

    // 
    glm::vec3 objectPosition = glm::vec3(1.0f);
    glm::mat4 objectTransform = glm::mat4(1.0f);

    objectTransform = glm::translate(objectTransform, objectPosition);
    //

    m_shader.Activate();
    m_shader.SetMatrix4f("vertexTransform", objectTransform);
}

void Mesh::Draw(Camera& m_CurrentCamera) {
    //
    m_shader.Activate();

    m_CurrentCamera.MatrixRender(m_shader, "camera_matrix");

    m_modelVertexArray.Bind();
    m_modelIndexBuffer.Bind();

    glDrawElements(GL_TRIANGLES, m_modelIndexBuffer.totalByteSize / sizeof(uint16_t), GL_UNSIGNED_SHORT, 0);

    m_modelVertexArray.Unbind();
    m_modelIndexBuffer.Unbind();
}