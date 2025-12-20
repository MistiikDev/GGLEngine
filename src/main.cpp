#include <iostream>
#include <core/window.h>

int main() {
    G_window gameWindow {"GGLEngine", 1920, 1080};
    
    gameWindow.Render();
    return 0;
}