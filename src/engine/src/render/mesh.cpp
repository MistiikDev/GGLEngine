#include <render/mesh.h>

Mesh::Mesh(GLShader* shader, std::vector<Vertex>& in_verticies, std::vector<uint32_t>& in_indicies, std::vector<Material>& meshMaterials)
    : m_shader(shader)
{
    verticies = std::move(in_verticies);
    indicies = std::move(in_indicies);
    materials = std::move(meshMaterials);

    //for (auto& m : materials) {
    //    if (!name_to_mat.count(m.name)) {
    //        name_to_mat[m.name] = m;
    //    }
    //} // Setup material hash map

    m_modelVertexArray = GLArray { };
    m_modelBuffer = GLBuf { };
    m_modelIndexBuffer = GLBuf { };

    m_modelBuffer.BufferData(verticies);
    m_modelIndexBuffer.BufferData(indicies);

    m_modelVertexArray.Bind();
    m_modelBuffer.Bind();
    m_modelIndexBuffer.Bind();

    //
    m_modelVertexArray.LinkAttribute(m_modelBuffer, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0); // Position Attribute
    m_modelVertexArray.LinkAttribute(m_modelBuffer, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)( 3 * sizeof(float))); // Color Attribute
    m_modelVertexArray.LinkAttribute(m_modelBuffer, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)( 6 * sizeof(float))); // TexUV Attribute
    m_modelVertexArray.LinkAttribute(m_modelBuffer, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)( 8 * sizeof(float))); // Normal Attribute
   
    m_modelVertexArray.Unbind();
    m_modelBuffer.Unbind();
    m_modelIndexBuffer.Unbind();

    // 
    glm::vec3 objectPosition = glm::vec3(0.0f);
    glm::mat4 objectTransform = glm::mat4(1.0f);

    objectTransform = glm::translate(objectTransform, objectPosition);
    //

    m_shader->Activate();
    m_shader->SetMatrix4f("vertexTransform", objectTransform);

}

void Mesh::Draw(Camera& m_CurrentCamera) {
    //
    m_shader->Activate();

    m_CurrentCamera.MatrixRender(*m_shader, "camera_matrix");

    m_modelVertexArray.Bind();
    m_modelIndexBuffer.Bind();

    m_shader->SetVector3f("material.ambiant", Vector3(1.0f));
    m_shader->SetVector3f("material.diffuse", Vector3(0.54f));
    m_shader->SetVector3f("material.specular", Vector3(0.5f));
    m_shader->SetFloat("material.shininess", 96.07f);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indicies.size()), GL_UNSIGNED_INT, nullptr);
    m_modelVertexArray.Unbind();
    m_modelIndexBuffer.Unbind();
}