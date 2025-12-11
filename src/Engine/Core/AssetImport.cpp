#include "AssetImport.h"

void AssetImport::logMessage(const char *log, bool m_skipNewLine = false)
{
    std::cout << "[ASSET IMPORTER] : " << log << (m_skipNewLine ? "" : "\n");
}

// Takes in an obj file, return a pipelined .gmld file for streaming later
void AssetImport::_write_GMDL_fromOBJ(const char* objDirectory, const char* targetDir)
{
    AssetImport::logMessage("Serializing OBJ file..");
    std::ifstream objFile(objDirectory);

    if (!objFile.is_open())
    {
        const char *errMessage = strcat("ERROR LOADING MODEL", objDirectory);
        AssetImport::logMessage(errMessage);

        throw EXIT_FAILURE;
    }

    std::string currentLineBuffer;

    std::vector<Vector3> positions;
    std::vector<Vector3> normals;
    std::vector<Vector2> texUV;

    std::map<Vertex, uint16_t, VertexHash> VertexToIndex;

    std::vector<Vertex> verticies;
    std::vector<uint16_t> indicies;

    std::unordered_map<Vertex, uint16_t, VertexHash> VertexToIndex();

    ///
    while (std::getline(objFile, currentLineBuffer))
    {
        std::stringstream tokenParser(currentLineBuffer);
        std::string keyword;

        tokenParser >> keyword;

        if (keyword == "v")
        {
            float v_x, v_y, v_z;
            tokenParser >> v_x >> v_y >> v_z;

            positions.push_back(Vector3(v_x, v_y, v_z));
        }
        else if (keyword == "vn")
        {
            float n_x, n_y, n_z;
            tokenParser >> n_x >> n_y >> n_z;

            normals.push_back(Vector3(n_x, n_y, n_z));
        }
        else if (keyword == "vt")
        {
            float t_x, t_y;
            tokenParser >> t_x >> t_y;

            texUV.push_back(Vector2(t_x, t_y));
        }
        else if (keyword == "f")
        {
            std::string vertData;
            std::vector<std::string> vertexIndexData;

            while (tokenParser >> vertData)
            {
                char delim = '/';
                std::string currentIndex;

                for (char element : vertData)
                {
                    if (element == delim)
                    {
                        vertexIndexData.push_back(currentIndex);
                        currentIndex.clear();
                    }
                    else
                    {
                        currentIndex += element;
                    }
                }

                vertexIndexData.push_back(currentIndex);
                vertexIndexData.clear();
                
                Vector3 vPos = stoi(vertexIndexData[0]) - 1 == -1 ? Vector3(0, 0, 0) : positions[stoi(vertexIndexData[0])  - 1];
                Vector2 vTexUV = stoi(vertexIndexData[1]) - 1 == -1 ? Vector2(0, 0) : texUV[stoi(vertexIndexData[1]) - 1];
                Vector3 vNorm = stoi(vertexIndexData[2]) - 1 == -1 ? Vector3(0, 0, 0) : normals[stoi(vertexIndexData[2]) - 1];
                
                vPos.print(true);
                vTexUV.print(true);
                vNorm.print(true);

                Vertex v;
                v.Position = vPos;
                v.TexUV = vTexUV;
                v.Normal = vNorm;

                verticies.push_back(v);

                if (VertexToIndex.count(v)) {
                    indicies.push_back(VertexToIndex[v]); // If vertex is already there, reuse its index and paste it into the indicies
                } else {
                    indicies.push_back(verticies.size() - 1);
                }
            }
        }

        // Save data from verticies and indicies vectors into binary
        std::ofstream target;
        target.open(targetDir, std::ios::binary);

        if (target.is_open()) {
            size_t verticies_size = sizeof(Vertex) * verticies.size();
            size_t indicies_size = sizeof(uint16_t) * indicies.size();

            std::cout << verticies_size << std::endl;
            std::cout << indicies_size << std::endl;

            target.write((char*)&verticies_size, sizeof(size_t));
            target.write((char*)&indicies_size, sizeof(size_t));

            target.write((char*)verticies.data(), verticies_size);
            target.write((char*)indicies.data(), indicies_size);
        } else {
            AssetImport::logMessage("ERROR WRITING BINARIES");
        }
    }   
}

G_Mesh AssetImport::_load_GMDL(const char* targetGMDL) {
    std::ifstream loadStream;

    G_Mesh gmdlMesh;

    loadStream.open(targetGMDL, std::ios::binary);

    if (loadStream.is_open()) {
        size_t verticies_count;
        size_t indicies_count;
        
        loadStream.read((char*)&verticies_count, sizeof(size_t));
        loadStream.read((char*)&indicies_count, sizeof(size_t));

        std::vector<Vertex> verticies(verticies_count);
        std::vector<uint16_t> indicies(indicies_count);

        loadStream.read((char*)verticies.data(), verticies_count * sizeof(Vertex));
        loadStream.read((char*)indicies.data(), indicies_count * sizeof(uint16_t));

    } else {
        AssetImport::logMessage("ERROR READING BINARIES");
        throw EXIT_FAILURE;
    }
}