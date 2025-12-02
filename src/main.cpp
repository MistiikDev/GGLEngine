#include <iostream>
#include "Window.h"

int main() {
    Window gameWindow {"GGLEngine", 1280, 720};
    
    gameWindow.Render();
    return 0;
}