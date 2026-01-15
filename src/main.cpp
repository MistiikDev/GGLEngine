#include <iostream>
#include <api/bootstrap/bootstrap.h>
#include <core/scene_window.h>

int main() {
    
    if ( Bootstrap::Init() ) {
        EditorViewport viewport {"GGLENGINE - VIEWPORT", 1280, 720};
    }

    EditorViewport viewport {"GGLENGINE - VIEWPORT", 1280, 720};
    viewport.Render();
    
    return 0;
}