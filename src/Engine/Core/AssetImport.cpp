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

    std::vector<OBJ_FaceData> faceData;
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

                OBJ_FaceData face;

                face.PositionIndex = vertexIndexData[0].empty() ? -1 : std::stoi(vertexIndexData[0]) - 1;
                face.UVIndex = vertexIndexData[1].empty() ? -1 : std::stoi(vertexIndexData[1]) - 1;
                face.NormalIndex = vertexIndexData[2].empty() ? -1 : std::stoi(vertexIndexData[2]) - 1;

                faceData.push_back(face);
            }
        }
    }

    for (size_t i = 1; i < faceData.size() - 1; i++) {
        // Triangulate n-gons from first vertex
        Vertex v0, vn, vn1;

        v0.Position = positions.at(faceData[0].PositionIndex);
        vn.Position = positions.at(faceData[i].PositionIndex);
        vn1.Position = positions.at(faceData[i + 1].PositionIndex);

        v0.TexUV = faceData[0].UVIndex == -1 ? Vector2(1.0f, 1.0f) : texUV.at(faceData[0].UVIndex);
        vn.TexUV = faceData[i].UVIndex == -1 ? Vector2(1.0f, 1.0f) : texUV.at(faceData[i].UVIndex);
        vn1.TexUV = faceData[i + 1].UVIndex == -1 ? Vector2(1.0f, 1.0f) : texUV.at(faceData[i + 1].UVIndex);

        v0.Normal = normals.at(faceData[0].NormalIndex);
        vn.Normal = normals.at(faceData[i].NormalIndex);
        vn1.Normal = normals.at(faceData[i + 1].NormalIndex);

        if (VertexToIndex.count(vn) == 0) {
            verticies.push_back(vn);
        }

        verticies.push_back(v0);
        verticies.push_back(vn);
        verticies.push_back(vn1);

        indicies.push_back(0);
        indicies.push_back(i);
        indicies.push_back(i + 1);
    }

    // Write vectors as bytes to file

    size_t vertex_count = verticies.size();
    size_t indicies_count = indicies.size();

    std::ofstream targetFile;
    std::string targetFileDir = std::string(targetDir) + ".gmdl";

    targetFile.open(targetFileDir, std::ios::binary);
    
    if (targetFile.is_open()) {
        // First 2 lines allocated to vertex and indicies count for allocation later
        targetFile.write((char*)&vertex_count, sizeof(size_t));
        targetFile.write((char*)&indicies_count, sizeof(size_t));

        targetFile.write((char*)verticies.data(), vertex_count * sizeof(Vertex));
        targetFile.write((char*)indicies.data(), indicies_count * sizeof(uint16_t));

        targetFile.close();
    } else {
        AssetImport::logMessage("ERROR CREATING BINARIES");
        throw EXIT_FAILURE;
    }
}

G_Model AssetImport::_load_GMDL(const char* targetGMDL) {
    std::ifstream loadStream;

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