#include "AssetImport.h"

void AssetImport::logMessage(const char* log, bool m_skipNewLine = false) {
    std::cout << "[ASSET IMPORTER] : " << log << (m_skipNewLine ? "" : "\n");
}

// Takes in an obj file, return a pipelined .gmld file for streaming later
void AssetImport::_write_GMDL_fromOBJ(const char* objDirectory) {
    AssetImport::logMessage("Serializing OBJ file..");

    std::ifstream objFile(objDirectory);

    if (!objFile.is_open()) {
        const char* errMessage = strcat("ERROR LOADING MODEL", objDirectory);
        AssetImport::logMessage(errMessage);

        throw EXIT_FAILURE;
    } 

    std::string dataBuffer;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texUV;

    ///
    while (std::getline(objFile, dataBuffer)) {
        std::stringstream tokenParser(dataBuffer);
        std::string keyword;

        tokenParser >> keyword; // Get first shift to keyword (1st element is keyword)

        if (keyword == "v") {
            float v_x, v_y, v_z;
            tokenParser >> v_x >> v_y >> v_z;

            positions.push_back(glm::vec3(v_x, v_y, v_z));

        } else if (keyword == "vn") {
            float n_x, n_y, n_z;
            tokenParser >> n_x >> n_y >> n_z;

            normals.push_back(glm::vec3(n_x, n_y, n_z));

        } else if (keyword == "vt") {
            float t_x, t_y;
            tokenParser >> t_x >> t_y;

            texUV.push_back(glm::vec2(t_x, t_y));
        }
    }
}