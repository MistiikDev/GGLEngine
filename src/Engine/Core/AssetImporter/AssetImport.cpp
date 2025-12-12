#include "AssetImport.h"

void AssetImport::logMessage(const char *log, bool b_skipNewLine = false)
{
    std::cout << "[ASSET IMPORTER] : " << log << (b_skipNewLine ? "" : "\n");
}

// Takes in an obj file, return a pipelined .gmld file for streaming later
void AssetImport::_write_GMDL_fromOBJ(const char *objDirectory, const char *targetDirectory)
{
    
}

G_Mesh AssetImport::_load_GMDL(const char *targetGMDL)
{   
    
}