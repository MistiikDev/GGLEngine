#include <iostream>
#include <core/window.h>

int main() {
    G_window gameWindow {"GGLEngine", 1280, 720};
    
    gameWindow.Render();
    return 0;
}