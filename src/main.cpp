#include <iostream>
#include "Window.h"

int main() {
    AssetImport::_write_GMDL_fromOBJ("src/Engine/Cop.obj", "src/copPak");
    AssetImport::_load_GMDL("src/copPak.gmdl");

    Window gameWindow {"GGLEngine", 1280, 720};
    
    gameWindow.Render();
    return 0;
}