#ifndef GGLENGINE_MESH_H
#define GGLENGINE_MODEL_H

#include <map>
#include <vector>

#include "Vertex.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Mesh {
    public:
        glm::vec3 Position;
        std::vector<Vertex> verticies;
        std::vector<unsigned int> indicies;

        Mesh(const std::vector<Vertex> in_verticies, const std::vector<unsigned int> in_indicies);
    private:
        VAO m_modelVertexArray;
        VBO m_modelBuffer;
        EBO m_modelIndexBuffer;
};

#endif