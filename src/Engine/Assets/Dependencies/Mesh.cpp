#include "Mesh.h"

const char* DEFAULT_FRAG_SHADER = "src/Engine/Graphics/Shaders/FShaders/default.frag";
const char* DEFAULT_VERT_SHADER = "src/Engine/Graphics/Shaders/VShaders/default.vert";

Mesh::Mesh(std::vector<Vertex>&& in_verticies, std::vector<uint32_t>&& in_indicies, std::vector<SubMesh>&& in_submeshes, std::vector<Material>&& meshMaterials)
    : m_shader(DEFAULT_VERT_SHADER, DEFAULT_FRAG_SHADER)
{
    verticies = std::move(in_verticies);
    indicies = std::move(in_indicies);
    sub_meshes = std::move(in_submeshes);
    materials = std::move(meshMaterials);

    for (auto& m : materials) {
        if (!name_to_mat.count(m.materialName)) {
            name_to_mat[m.materialName] = m;
        }
    } // Setup material hash map

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

    // Instead of rendering the whole batch of verticies, render them per submesh groups, and color them accordingly
    for (auto& submesh : sub_meshes) {
        if (submesh.materialName.empty()) {
            std::cerr << "[Render] Submesh without material\n";
            continue;
        }

        Material mat = name_to_mat[submesh.materialName];
        
        m_shader.Activate();

        m_shader.SetVector3f("material.ambiant", mat.ambiantColor);
        m_shader.SetVector3f("material.diffuse", mat.diffuseColor);
        m_shader.SetVector3f("material.specular", mat.specularColor);
        m_shader.SetFloat("material.shininess", mat.specular_factor);

        glDrawElements(GL_TRIANGLES, submesh.indiciesCount, GL_UNSIGNED_INT, (void*)(submesh.indiciesOffset * sizeof(uint32_t)));
    }

    m_modelVertexArray.Bind();
    m_modelIndexBuffer.Bind();
}