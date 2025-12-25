#include <render/mesh.h>
#include <asset/import/obj_import.h>

Mesh::Mesh(GLShader* shader, OBJ_Data* obj_data, MTL_Data* mtl_data)
    : m_shader(shader)
{
    // Get ownership of important data
    verticies = std::move(obj_data->vertices);
    indicies = std::move(obj_data->indicies);
    material_range = std::move(mtl_data->matToRange);
    material_hash = std::move(mtl_data->nameToMat);
    //


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

    for (auto const& kv : material_range) {
        std::string matName = kv.first; 
        std::vector<UI32_Range> matRanges = kv.second;

        const Material& mat = material_hash[matName];

        for (UI32_Range& range : matRanges) {
            m_shader->SetVector3f("material.ambiant", mat.ambiantColor);
            m_shader->SetVector3f("material.diffuse", mat.diffuseColor);
            m_shader->SetVector3f("material.specular", mat.specularColor);
            m_shader->SetFloat("material.shininess", mat.specular_factor);

            void* offset = (void*)(uintptr_t)(range.start * sizeof(unsigned int));

            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(range.end - range.start), GL_UNSIGNED_INT, offset);
        }
    }

    m_modelVertexArray.Unbind();
    m_modelIndexBuffer.Unbind();
}