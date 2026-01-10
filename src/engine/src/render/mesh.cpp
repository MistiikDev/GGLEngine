#include <render/GLMesh.h>



GLMesh::GLMesh(GLShader* shader, GLMesh_Data& obj_data, GLMaterial_Data& mtl_data)
    : m_shader(shader)
{
    // Get ownership of important data
    GLMesh_data = obj_data;
    GLMaterial_data = mtl_data;

    for (auto const& subGLMesh : GLMesh_data.sub_GLMeshes) {
        GLMaterial* GLMaterial = subGLMesh.GLMaterial;

        m_shader->Activate();

        if (GLMaterial == nullptr) {
            GLMaterial = DefaultAssets::debug_GLMaterial;
        }

        if (GLMaterial->diffuseTex == nullptr) {
            GLMaterial->diffuseTex = DefaultAssets::white_texture;
        }
        
        if (GLMaterial->specularTex == nullptr) {
            GLMaterial->specularTex = DefaultAssets::white_texture;
        }
    }

    m_modelVertexArray = GLArray { };
    m_modelBuffer = GLBuf { };
    m_modelIndexBuffer = GLBuf { };

    m_modelBuffer.BufferData(GLMesh_data.vertices);
    m_modelIndexBuffer.BufferData(GLMesh_data.indicies);

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

    transform = Transform( objectTransform );

    //
    m_shader->Activate();
    m_shader->SetMatrix4f("vertexTransform", transform.toMatrix());
}

void GLMesh::Draw(Camera& m_CurrentCamera) {
    //
    m_shader->Activate();
    m_shader->SetMatrix4f("vertexTransform", transform.toMatrix());
    
    m_CurrentCamera.MatrixRender(*m_shader, "camera_matrix");

    m_modelVertexArray.Bind();
    m_modelIndexBuffer.Bind();

    for (auto const& subGLMesh : GLMesh_data.sub_GLMeshes) {
        const GLMaterial* GLMaterial = subGLMesh.GLMaterial;

        m_shader->Activate();

        GLMaterial->diffuseTex->Bind(0);
        GLMaterial->diffuseTex->Sample(*m_shader, 0, "diffuseMap");

        GLMaterial->specularTex->Bind(1);
        GLMaterial->specularTex->Sample(*m_shader, 1, "specularMap");

        m_shader->SetFloat("GLMaterial.shininess", GLMaterial->specular_factor);
        m_shader->SetVector3f("GLMaterial.ambient", GLMaterial->ambiantColor);
        m_shader->SetVector3f("GLMaterial.diffuse", GLMaterial->diffuseColor);
        m_shader->SetVector3f("GLMaterial.specular", GLMaterial->specularColor);

        void* offset = (void*)(uintptr_t)(subGLMesh.indexOffset * sizeof(uint32_t));

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(subGLMesh.indexCount), GL_UNSIGNED_INT, offset);

        GLMaterial->diffuseTex->Unbind(0);
        GLMaterial->specularTex->Unbind(1);
    }

    m_modelVertexArray.Unbind();
    m_modelIndexBuffer.Unbind();
}