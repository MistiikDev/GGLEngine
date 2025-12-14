#include <iostream>
#include "Window.h"

int main() {
    Window gameWindow {"GGLEngine", 1920, 1080};
    
    gameWindow.Render();
    return 0;
}