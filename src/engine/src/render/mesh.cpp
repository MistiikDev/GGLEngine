#include <render/mesh.h>

Mesh::Mesh(GLShader* shader, Mesh_Data& obj_data, Material_Data& mtl_data)
    : m_shader(shader)
{
    // Get ownership of important data
    mesh_data = obj_data;
    material_data = mtl_data;

    for (auto const& submesh : mesh_data.sub_meshes) {
        Material* material = submesh.material;

        m_shader->Activate();

        if (material == nullptr) {
            material = DefaultAssets::debug_material;
        }

        if (material->diffuseTex == nullptr) {
            material->diffuseTex = DefaultAssets::debug_texture;
        }
        
        if (material->specularTex == nullptr) {
            material->specularTex = DefaultAssets::debug_texture;
        }
    }

    m_modelVertexArray = GLArray { };
    m_modelBuffer = GLBuf { };
    m_modelIndexBuffer = GLBuf { };

    m_modelBuffer.BufferData(mesh_data.vertices);
    m_modelIndexBuffer.BufferData(mesh_data.indicies);

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

    cframe = CFrame( objectTransform );

    //
    m_shader->Activate();
    m_shader->SetMatrix4f("vertexTransform", cframe.toMatrix());
}

void Mesh::Draw(Camera& m_CurrentCamera) {
    //
    m_shader->Activate();
    m_shader->SetMatrix4f("vertexTransform", cframe.toMatrix());
    
    m_CurrentCamera.MatrixRender(*m_shader, "camera_matrix");

    m_modelVertexArray.Bind();
    m_modelIndexBuffer.Bind();

    for (auto const& submesh : mesh_data.sub_meshes) {
        const Material* material = submesh.material;

        m_shader->Activate();

        material->diffuseTex->Bind(0);
        material->diffuseTex->Sample(*m_shader, 0, "diffuseMap");

        material->specularTex->Bind(1);
        material->specularTex->Sample(*m_shader, 1, "specularMap");

        m_shader->SetFloat("material.shininess", material->specular_factor);
        m_shader->SetVector3f("material.ambient", material->ambiantColor);
        m_shader->SetVector3f("material.diffuse", material->diffuseColor);
        m_shader->SetVector3f("material.specular", material->specularColor);

        void* offset = (void*)(uintptr_t)(submesh.indexOffset * sizeof(uint32_t));

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(submesh.indexCount), GL_UNSIGNED_INT, offset);

        material->diffuseTex->Unbind(0);
        material->specularTex->Unbind(1);
    }

    m_modelVertexArray.Unbind();
    m_modelIndexBuffer.Unbind();
}