#include <scene/scene.h>

void G_scene::Load() const {
    // TODO: Have it load from a .scene file maybe... 
    // For now load default things

    Entity e1 = Entity {};
    e1.AddComponent<TRANSFORM>(0, 0);
    e1.AddComponent<MESH>();
}